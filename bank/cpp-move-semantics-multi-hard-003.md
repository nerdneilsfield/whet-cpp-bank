---
qid: cpp-move-semantics-multi-hard-003
type: multi
kp: [cpp-move-semantics]
difficulty: hard
answer_key: [A, C, D]
---
关于在 `const` 对象上使用 `std::move`，以下说法正确的是哪些？

```cpp
std::string make() {
    const std::string s = "hello";
    return std::move(s);   // (1)
}

std::vector<std::string> v;
const std::string cs = "x";
v.push_back(std::move(cs));   // (2)
```

A. `std::move(s)` 仅做 `static_cast<const std::string&&>(s)`，得到的是**const 右值引用**，能匹配的构造函数只有拷贝构造（接受 `const T&`），不能匹配移动构造（接受 `T&&`）。
B. `std::move(s)` 会强制调用移动构造函数，把 const 对象的内容掏空，因此对 const 局部变量使用 move 是危险且未定义的行为。
C. (1) 中由于 `s` 是 `const`，`std::move(s)` 退化为拷贝；同时还禁用了 NRVO/隐式移动，使该写法严格劣于直接 `return s;`。
D. (2) 编译通过且语义正确，但实际行为是拷贝构造 `std::string`，达不到 move 的性能预期，是"伪 move"。

---

**解析：**

A 正确：`std::move` 只是类型转换不改变常量性，`std::move(const T)` 得到 `const T&&`；移动构造形参是 `T&&`（非 const），无法绑定到 `const T&&`，重载解析回退到 `const T&` 的拷贝构造。
B 错误：上面已经分析，结果是回退到拷贝，并非"强制调用移动构造"也非"未定义行为"，是编译期可决议的安全退化。
C 正确：在 `return` 语句中显式 `std::move` 会破坏 NRVO/隐式移动条件（标准要求 return 表达式是 id-expression 引用的局部对象），加上 const 又不能真 move，所以这种写法对性能完全是负优化。
D 正确：(2) 编译合法，重载解析选了 `push_back(const string&)`，效果是拷贝，不是 move，体现了"加了 move 也没用"的典型坑。

## Explanation

A、C、D 正确：`std::move` 只是类型转换，不会去掉 `const`，因此 `const T` 被移动后得到的是 `const T&&`，通常只能匹配拷贝构造。对 `const` 局部返回时手写 `std::move` 还会破坏 NRVO 或隐式移动条件。常见误区是认为写了 `std::move` 就一定发生移动；它只允许移动，不能强制移动。
