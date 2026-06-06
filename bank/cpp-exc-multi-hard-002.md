---
qid: cpp-exc-multi-hard-002
type: multi
kp: [cpp-exceptions]
difficulty: hard
answer_key: [A, B, D]
---
关于栈展开过程中抛出第二个异常，以下说法正确的是哪些？

```cpp
struct Bad {
    ~Bad() { throw 2; }            // 析构中抛异常
};

void f() {
    Bad b;
    throw 1;                       // (1) 触发栈展开，析构 b 又抛
}
```

A. 当栈展开过程中又抛出新异常（且未被立即捕获），编译器调用 `std::terminate` 终止程序——这是 C++ 异常机制的硬性规则。
B. `std::uncaught_exceptions()`（C++17，返回 int）可在析构函数中检测当前是否处于栈展开过程中，从而决定是否抛新异常。
C. 析构函数可以抛异常，只要被立即就地捕获（在析构函数内 try/catch）就完全等价于普通函数，没有任何风险。
D. RAII 类型（如 `std::lock_guard`）的析构函数被隐式 `noexcept`；若析构中抛异常会直接 terminate，这是 C++11 决议——析构默认 `noexcept(true)`。

---

**解析：**

A 正确：栈展开过程中如有未处理的新异常逸出（例如 `Bad::~Bad` 抛出 `2`），异常处理机制无法同时处理两个，按规则调用 `std::terminate`。这是 C++ 异常安全的核心约束。

B 正确：C++17 的 `std::uncaught_exceptions()` 返回当前活跃异常数（int），在析构中判断 `>0` 即处于栈展开期，可避免再次抛出。Herb Sutter 提出此 API 替代 C++03 的 `uncaught_exception()`（bool）。

C 错误：即便析构函数内 try/catch 看似安全，但若**异常逃出析构函数**（catch 后又 rethrow，或异常类型不匹配）仍会触发 terminate 风险；更重要的是，析构函数默认是 `noexcept`，逃逸异常直接 terminate，并非"无任何风险"。

D 正确：C++11 起隐式规则——析构函数默认是 `noexcept(true)`（除非基类/成员析构非 noexcept，或显式标注 `noexcept(false)`），从析构中抛异常会直接 terminate，是 C++11 的重大变更。

## Explanation

A、B、D 正确：栈展开期间如果析构函数又让新异常逃逸，运行时会调用 `std::terminate`。`std::uncaught_exceptions()` 可用于识别当前是否处于异常展开中，但更好的设计是析构函数不抛出。常见误区是认为析构里局部 try/catch 就完全安全；只要异常逃出默认 `noexcept` 析构，仍会终止程序。
