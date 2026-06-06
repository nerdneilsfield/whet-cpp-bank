---
qid: cpp-taste-conc-001
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: C
tags: [code-taste, best-practice]
---
四个人为同一段"保护单个 mutex 下的临界区"代码提交了四种写法，功能完全相同。哪一种**最值得通过 review**？

```cpp
class Counter {
    std::mutex mu_;
    int n_ = 0;
public:
    // A
    void inc_a() {
        std::scoped_lock lock(mu_);
        ++n_;
    }

    // B
    void inc_b() {
        std::unique_lock<std::mutex> lock(mu_);
        ++n_;
    }

    // C
    void inc_c() {
        std::lock_guard<std::mutex> lock(mu_);
        ++n_;
    }

    // D
    void inc_d() {
        mu_.lock();
        ++n_;
        mu_.unlock();
    }
};
```

A. A — `scoped_lock` 是 C++17 后最新的统一选择，永远用它就对
B. B — `unique_lock` 最灵活，可以延迟锁定、转移所有权，未来要扩展也方便
C. C — `lock_guard` 是 RAII 单锁的最小开销，意图最窄，恰好契合这里的场景
D. D — 显式 `lock/unlock` 最直观，把同步动作摆在明面上

---

**解析：**

选 C。这道题考的是 **"用语义最窄的工具表达最窄的意图"**。

`lock_guard` 自 C++11 就是为"作用域内持有一把锁、不需要任何额外能力"这件事专门设计的：构造即 lock、析构即 unlock，没有移动、没有延迟、没有 try_lock、没有条件变量配合。整个类只有锁和构造/析构两件事，**没有任何运行时分支**。

逐一品味为什么其他版本不好：

- **A**：`scoped_lock` 是 C++17 引入的，**核心价值是"一次性加多把锁并防死锁"**（变参模板 + `std::lock` 算法）。用它锁单个 mutex 也能跑，但传达的是"我可能要锁多个"的信号——读者读到 `scoped_lock` 会下意识找"另一把锁在哪"。在只锁一把的地方用它，是**词不达意**。
- **B**：`unique_lock` 体积更大（要存"是否拥有锁"的 bool 标记）、支持 `defer_lock` / `try_to_lock` / `unlock()` / 移动语义，是配合 `condition_variable::wait` 或需要中途解锁的场景。在简单临界区用它，是**用大锤敲钉子**——多一份运行时状态、多一层语义负担。
- **D**：手写 `lock/unlock` 是**异常不安全**的反面教材——`++n_` 看起来不会抛，但稍微复杂一点的临界区一旦中间抛异常，`unlock()` 就被跳过，锁永久泄漏、整个程序死锁。这是 C 时代写 pthread 的味道。

**核心识别点：**

- 单一 mutex + 作用域加锁 → `lock_guard`
- 多个 mutex 同时加 → `scoped_lock`（C++17）
- 需要配合 `condition_variable::wait` / 延迟加锁 / 中途解锁 → `unique_lock`
- 看见显式 `lock()`/`unlock()` 配对 → 警觉，是不是该 RAII

A 选项的"用最新的就对"是典型的新人误判——C++ 的工具选择**不是按版本号排队**，而是按语义匹配度。`scoped_lock` 并没有"取代" `lock_guard`，它解决的是另一个问题（多锁原子加锁）。把 `scoped_lock` 当作"`lock_guard` 2.0"是常见的错读。

B 选项的"以后扩展方便"是"过度灵活"的典型借口——**等真要扩展时再改成 `unique_lock` 是分分钟的事**，提前埋下不必要的开销才是味道差。

**来源：** 手写题。语义区分见 ISO/IEC 14882:2017 §33.4.4 [thread.lock]；Herb Sutter "GotW #59: Using the Standard Library"；Anthony Williams *C++ Concurrency in Action* 2e 第 3 章。

## Explanation

正确答案是 C。这道题考的是 "用语义最窄的工具表达最窄的意图"。
`lock_guard` 自 C++11 就是为"作用域内持有一把锁、不需要任何额外能力"这件事专门设计的：构造即 lock、析构即 unlock，没有移动、没有延迟、没有 try_lock、没有条件变量配合。
把 `scoped_lock` 当作"`lock_guard` 2.0"是常见的错读。
