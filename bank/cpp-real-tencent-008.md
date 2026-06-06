---
qid: cpp-real-tencent-008
type: single
kp: [cpp-exceptions, cpp-special-members]
primary_kp: cpp-exceptions
difficulty: hard
answer_key: B
tags: [interview-real, tencent]
---
```cpp
class Bad {
public:
    ~Bad() {
        throw std::runtime_error("oops");   // 危险！
    }
};

void f() {
    Bad b1;
    Bad b2;
    throw std::logic_error("trigger stack unwinding");
    // 异常向外传播 → 栈展开 → b2、b1 依次析构
    //   b2 析构时抛 runtime_error → 此时已有 logic_error 在飞行
}
```
为什么 C++ 中析构函数**不应该**抛异常？

A. C++ 标准明文禁止析构函数抛异常，否则编译报错
B. 在异常栈展开期间，已有一个异常在飞行；如果此时另一个析构再抛异常，C++ 运行时无法处理两个同时活动的异常，会调用 std::terminate 直接终止程序
C. 析构函数抛异常会导致内存泄漏，无法被 RAII 回收
D. 析构函数没有返回值，所以抛异常无法被捕获

---

**解析：**

选 B。这是 C++ 异常机制的硬性约束。

**栈展开（stack unwinding）机制：**
当 `throw` 一个异常时，C++ 运行时会：
1. 从当前作用域向上展开栈
2. 析构每个作用域中的局部对象
3. 直到找到匹配的 `catch` 块

**两个异常并发的问题：**
如果在栈展开过程中（已有异常在飞行），析构函数又抛出新异常，C++ 运行时**无法选择**应该传播哪一个 → 行为未定义 → 标准规定调用 `std::terminate()` → 程序立即终止（不再析构其他对象）。

**最佳实践：**
1. 析构函数标记为 `noexcept`（C++11 默认隐式 noexcept）
2. 如果必须有可能失败的清理操作，try-catch 吞掉异常并记录日志：
```cpp
~Resource() noexcept {
    try { release(); }
    catch (...) { /* log */ }
}
```
3. 提供单独的 `close()` 方法供用户主动调用（这样可以抛异常给用户处理）

A 错，标准没禁止，但默认 noexcept。C 错，析构抛异常不一定泄漏（具体情况复杂），主要问题是 terminate。D 错，与返回值无关。

**来源：** 腾讯 C++ 面试（参考：Effective C++ Item 8、C++ Core Guidelines E.16）