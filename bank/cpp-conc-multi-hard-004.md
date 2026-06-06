---
qid: cpp-conc-multi-hard-004
type: multi
kp: [cpp-concurrency]
difficulty: hard
answer_key: [A, B, D]
---
关于双重检查锁定（Double-Checked Locking）实现的单例，以下说法正确的是哪些？

```cpp
// 经典坏版本
Singleton* getInstance() {
    if (instance == nullptr) {
        std::lock_guard<std::mutex> lk(mu);
        if (instance == nullptr) {
            instance = new Singleton();   // (X)
        }
    }
    return instance;
}
```

A. 上述写法在 C++11 之前是经典 broken DCLP：(X) 中"分配内存"、"构造对象"、"指针赋值"可以被编译器/CPU 重排，其他线程可能读到非 nullptr 但未完成构造的对象。
B. 正确做法之一是把 `instance` 改为 `std::atomic<Singleton*>`，外层 load 用 `memory_order_acquire`，赋值用 `memory_order_release`，建立同步关系。
C. 用普通 `volatile` 关键字修饰 `instance` 就足以修复 DCLP——因为 `volatile` 提供了跨线程的同步保证。
D. C++11 起，最简洁正确的单例写法是局部 `static` 变量（Meyers' Singleton），标准保证初始化线程安全且无双重初始化。

---

**解析：**

A 正确：未加同步的指针读写在弱内存模型上可重排，DCLP 的经典 bug 正是其他线程看到非空指针但对象未构造完成；这是 1990 年代以来著名的论文 "Double-Checked Locking is Broken" 描述的问题。
B 正确：用原子指针配合 release-acquire 是合法 DCLP 实现：写线程 release 完成构造与赋值；读线程 acquire 看到非 nullptr 时，构造已完成。
C 错误：`volatile` 在 C++ 中**不是同步原语**，只阻止编译器优化但不强制 CPU 内存屏障，不能解决跨线程可见性与重排问题（Java 的 `volatile` 才有 acquire/release 语义，C++ 没有）。
D 正确：C++11 [stmt.dcl]/4 保证函数局部 static 的初始化是线程安全的（"magic statics"），Meyers' Singleton 是最简洁且正确的方案，且零开销（首次后无锁）。

## Explanation

A、B、D 正确：坏的双重检查锁定可能让其他线程看到非空指针但对象尚未构造完成。正确实现需要原子指针配合 release/acquire，或更简单地使用 C++11 保证线程安全初始化的局部 static。常见误区是把 C++ 的 `volatile` 当成同步原语；它不提供跨线程 happens-before。
