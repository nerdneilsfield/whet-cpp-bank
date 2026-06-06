---
qid: cpp-real-quiz-026
type: single
kp: [cpp-cpp11, cpp-concurrency]
primary_kp: cpp-cpp11
difficulty: medium
answer_key: A
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，关于以下函数中的 `static` 局部变量初始化，正确的描述是？

```cpp
int getValue() {
    static int v = computeExpensive();  // 假设耗时
    return v;
}
```

A. C++11 起，标准保证 static 局部变量的初始化是线程安全的（"magic statics"）
B. 必须自己加 mutex 才线程安全
C. 线程安全是实现定义
D. 静态局部变量不能被并发访问

---

**解析：**

[stmt.dcl]/4（C++11 引入，又称 "magic statics" / function-local static initialization）：

> If control enters the declaration concurrently while the variable is being initialized, the concurrent execution shall wait for completion of the initialization.

也就是说编译器**必须**生成同步代码（GCC 用 `__cxa_guard_acquire/release`，MSVC 用类似机制），保证多线程并发调用 `getValue()` 时 `computeExpensive()` 只执行一次，且其它线程会等待初始化完成。

这是 Meyers 单例模式（Meyers' Singleton）成为推荐写法的标准支撑：

```cpp
T& instance() {
    static T inst;     // C++11 起线程安全
    return inst;
}
```

C++03 时代这种代码不安全，DCLP（双重检查锁定）才是常规做法。MSVC 2015+ 才完整实现这一保证。

**来源：** C++11 [stmt.dcl]/4；Meyers' Singleton