---
qid: cpp-move-adv-012
type: single
kp: [cpp-move-semantics]
difficulty: medium
answer_key: C
---

下面代码用 `std::move` 替换 `std::forward`，会产生什么问题？

```cpp
template<typename T>
void broken_wrapper(T&& arg) {
    target(std::move(arg));   // ← 错误做法
}

std::string s = "hello";
broken_wrapper(s);   // (1) 传左值
```

调用 (1) 后，`s` 的状态是什么？

A. `s` 保持 `"hello"` 不变，因为 `std::move` 对左值无效
B. `s` 保持 `"hello"` 不变，因为 `target` 有 `const&` 重载会被优先选中
C. `s` 变成**未指定状态**（moved-from），因为 `std::move` 无条件将 `arg` 转为右值引用，触发移动构造/移动赋值
D. 编译报错，`std::move` 不能作用于左值

---

**解析：**

`std::move(arg)` 等价于 `static_cast<std::remove_reference_t<T>&&>(arg)`，**无论 T 是什么，结果始终是右值引用**。

当调用 `broken_wrapper(s)` 时：
- T 推导为 `std::string&`，arg 绑定到 `s`。
- `std::move(arg)` 将 `s` 强转为 `std::string&&`。
- `target` 的移动重载被调用，`s` 的内部资源被移走，进入未指定状态（valid but unspecified）。

这是完美转发里的经典错误：**对左值参数用 `std::move` 会意外移走调用方的对象**。正确做法是用 `std::forward<T>(arg)`，它在 T = `std::string&` 时返回左值引用，不会移走资源。

选 C。
