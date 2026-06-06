---
qid: cpp-exc-multi-hard-001
type: multi
kp: [cpp-exceptions]
difficulty: hard
answer_key: [A, B, D]
---
关于 `noexcept` 说明符的语义，以下说法正确的是哪些？

```cpp
void f() noexcept { throw 1; }     // (1)

template<typename T>
void g(T t) noexcept(noexcept(t.foo())) { t.foo(); }   // (2)

struct S {
    S(S&&) noexcept;                // (3) move 构造
    ~S() noexcept(false);           // (4)
};
```

A. 标记 `noexcept` 的函数若实际抛出异常，会直接调用 `std::terminate`，而**不会**进行栈展开（unwinding 可能但实现允许跳过）。
B. (3) 标准库容器如 `std::vector` 在扩容（reallocation）时，若元素 move 构造是 `noexcept` 则用 move，否则用 copy——`noexcept` 直接影响性能优化。
C. 函数析构默认是 `noexcept(true)`，C++11 起即便用户写 `~S() {}` 也无法让它抛出异常——析构函数永远禁止抛出。
D. (2) 的 `noexcept(expr)` 中内层 `noexcept(t.foo())` 是 noexcept 运算符，在编译期判断表达式是否声明不抛出，外层 `noexcept(...)` 是说明符——这是常见的"条件性 noexcept"模式。

---

**解析：**

A 正确：noexcept 函数抛异常时直接 `std::terminate`，并且**不保证**栈展开（编译器可以省略 unwind tables 优化代码尺寸），导致 RAII 不被执行。这是 noexcept 比 throw spec 更严格之处。

B 正确：标准要求 `std::vector::push_back` 等扩容操作在元素 move 构造非 noexcept 时退化为 copy（strong exception guarantee）；提供 `noexcept` move 是实现高性能容器的关键，Effective Modern C++ Item 14 详述。

C 错误：析构函数默认是 `noexcept(true)`，但用户**可以**显式声明 `~S() noexcept(false)` 让析构允许抛异常（如 (4)）。不过强烈不推荐——异常在栈展开中再抛会直接 `terminate`。

D 正确：`noexcept(expr)` 是双重语义：作为说明符 `noexcept(bool_expr)`，里面的 `noexcept(other_expr)` 是 noexcept 运算符（编译期检查表达式是否潜在抛出）。组合使用实现"如果 t.foo() 不抛，则本函数也不抛"的条件转发。

## Explanation

A、B、D 正确：`noexcept` 是运行时硬承诺，违背时调用 `std::terminate`，不保证正常栈展开。容器会利用移动构造是否 `noexcept` 来决定扩容时移动还是拷贝，以维护强异常保证。常见误区是把 `noexcept(expr)` 的说明符和内部的 noexcept 运算符混淆。
