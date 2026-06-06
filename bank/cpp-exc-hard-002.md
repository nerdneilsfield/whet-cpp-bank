---
qid: cpp-exc-hard-002
type: single
kp: [cpp-exceptions]
difficulty: hard
answer_key: C
---

C++11 之后，下列析构函数是否能编译/运行？

```cpp
struct R {
    ~R() { throw std::runtime_error("oops"); }
};

void f() {
    R r;
}
```

A. 编译失败，析构函数中不允许 `throw`
B. 编译成功，正常抛出并被外层 `catch` 捕获
C. 编译成功，但因为 C++11 起析构函数默认隐式声明为 `noexcept(true)`，从中抛出异常会直接调用 `std::terminate()`。要允许，需 `~R() noexcept(false) { throw std::runtime_error("oops"); }`
D. C++17 起析构函数被强制为 `noexcept`，无法关闭

## Explanation

C++11 引入了"隐式 `noexcept` 析构"规则：所有特殊成员函数（包括析构）默认按以下规则推导异常规范——若所有调用都不抛，则推为 `noexcept(true)`，否则 `noexcept(false)`。在最简类中（无成员、无 throw 调用），析构默认 `noexcept(true)`。从 `noexcept(true)` 函数抛出异常的行为是：**先尝试匹配 `catch`，找不到则直接 `terminate`，不再做任何栈展开**——即使你在函数内层加了 `try/catch`，只要异常逃出 `noexcept` 边界即终止。要显式允许抛出，必须写 `~R() noexcept(false)`。但即便如此，前题（cpp-exc-hard-001）的"展开期再抛"风险仍然存在。
