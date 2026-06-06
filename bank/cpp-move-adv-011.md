---
qid: cpp-move-adv-011
type: single
kp: [cpp-move-semantics]
difficulty: medium
answer_key: A
---

比较下面两个 `wrapper` 的实现，哪个描述**正确**？

```cpp
// 版本 1：完美转发
template<typename... Args>
void wrapper1(Args&&... args) {
    target(std::forward<Args>(args)...);
}

// 版本 2：直接传递（不用 forward）
template<typename... Args>
void wrapper2(Args&&... args) {
    target(args...);
}
```

```cpp
std::string s = "hello";
wrapper1(s);         // (A) 传左值，target 收到 string&
wrapper1(std::string("world")); // (B) 传右值，target 收到 string&&

wrapper2(s);         // (C) 传左值，target 收到 ?
wrapper2(std::string("world")); // (D) 传右值，target 收到 ?
```

A. `wrapper2` 中 (C) 和 (D) 的 `target` 均收到左值引用（`string&`），因为具名形参是左值
B. `wrapper2` 中 (C) 收到左值引用，(D) 收到右值引用，行为与 `wrapper1` 相同
C. `wrapper2` 完全等价于 `wrapper1`，`std::forward` 没有实际作用
D. `wrapper2` 中 (D) 会触发编译错误

---

**解析：**

`wrapper2` 里形参 `args...` 虽然推导类型含 `&&`，但**具名变量在表达式中是左值**（named lvalue rule）。

- (C)：`s` 传入，`args` 绑定到 `string&`，`target(args...)` 传的是左值引用——正确。
- (D)：`string("world")` 传入，`args` 是 `string&&` 类型的具名变量，但使用 `args` 表达式时它是左值，`target(args...)` 仍传左值引用——**原来的右值移动语义丢失**，target 得到的是 `string&` 而非 `string&&`，可能触发拷贝构造而非移动构造。

选 A（两者都收到左值引用）。`std::forward` 的作用就是恢复原始值类别，不用它就会"遗忘"右值身份。

## 解析

正确答案是 A，`wrapper2` 中的 `args` 是具名形参，作为表达式使用时一定是左值。即使调用方传入右值，直接写 `target(args...)` 也会把它们按左值传出。`std::forward<Args>(args)...` 的作用正是恢复每个实参原来的值类别。
