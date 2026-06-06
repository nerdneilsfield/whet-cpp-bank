---
qid: cpp-taste-init-007
type: single
kp: [cpp-cpp11, cpp-stl-basics]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: C
tags: [code-taste, best-practice, lazy-init, thread-safety]
---
一个昂贵的全局对象 `Logger`，要求**第一次被用到时才构造**，且**线程安全**。四个延迟初始化方案哪个最有品味？

```cpp
// A
Logger& get_logger() {
    static Logger* p = nullptr;
    if (!p) {
        static std::mutex m;
        std::lock_guard lock(m);
        if (!p) p = new Logger();
    }
    return *p;
}

// B
Logger& get_logger() {
    static std::once_flag flag;
    static Logger* p = nullptr;
    std::call_once(flag, []{ p = new Logger(); });
    return *p;
}

// C
Logger& get_logger() {
    static Logger instance;
    return instance;
}

// D
Logger& get_logger() {
    static std::optional<Logger> instance;
    static std::mutex m;
    std::lock_guard lock(m);
    if (!instance) instance.emplace();
    return *instance;
}
```

A. A — 经典双检查锁 (DCLP)，性能最好（fast path 无锁）
B. B — `std::call_once` 是标准提供的"只做一次"工具，最规范
C. C — 函数内 `static` 局部对象，依赖 C++11 magic statics
D. D — `std::optional` 显式 lazy + mutex 守护，最直观

---

**解析：**

选 C。这道题考 **"函数内 `static` 局部变量（magic statics）在 C++11 起就是线程安全的延迟初始化"** ——这条规则改变了一切，但很多人没跟上。

逐一品味：

- **A** **C++11 之前**人们用过的双检查锁定 (DCLP)。在没有 memory model 的语言（C++03）里，DCLP **是 broken 的**——Scott Meyers 和 Andrei Alexandrescu 2004 年的著名论文 ["C++ and the Perils of Double-Checked Locking"](https://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf) 证明：编译器/CPU 重排可能让另一个线程看到 `p != nullptr` 但 `Logger` 还没构造完。**即使加 `volatile` 也不够**——`volatile` 在 C++ 里不是内存屏障。要写对，需要 C++11 的 `std::atomic<Logger*>` + `memory_order_acquire/release`。题目里给的 A 是裸 `Logger*`，**未定义行为**。
- **B** `std::call_once` 是 C++11 给"只执行一次"提供的标准工具，写法正确、行为正确。但**就这场景**而言，它**比 magic statics 更繁琐**：你要管理 `once_flag`、还要 raw `new`（谁 delete？这里就泄漏了——程序退出时不调用析构）。`call_once` 真正的场景是**初始化逻辑必须在某个对象方法里被触发、但绑到 once_flag 上**（比如类的成员级懒初始化），不是函数级单例。
- **C** **C++11 起的 magic statics**：标准 §6.7.4 [basic.start.term] 和 §9.7 [stmt.dcl]/4 保证：
  1. **首次进入声明时构造**——天然 lazy
  2. **多线程并发到达此处时，只有一个线程执行构造，其他线程阻塞等待**——天然线程安全（编译器实现成内部用 `once_flag` + 一个 atomic guard byte）
  3. **程序退出时按反构造顺序析构**——无泄漏
  4. **快速路径**（已构造后再调用）是**一次 atomic load + branch**，几乎零成本
  一行代码同时拿到 A 想要的性能、B 想要的正确性、还附送 D 没有的自动析构。这是 Meyers' Singleton 模式在 C++11 之后的"终于一行就对了"形态。
- **D** 用 `optional` + `mutex` 是"我不知道 magic statics 可以"的人手写出来的等价物——每次调用都要 lock 一次 mutex（fast path 也付出锁开销），比 C 慢一个数量级。如果你**真的需要重置/销毁后重新构造**，`optional` 才有它的位置——但题目要求"第一次用到时构造"，单向懒，optional 是过度设计。

**核心识别点**：

- 函数内 `static T x = ...;` 在 **C++11 起线程安全 + 延迟构造 + 自动析构**——这是 Meyers' Singleton 的正解
- 双检查锁定 (DCLP) 在 C++11 之前是错的；之后用 magic statics 替代，不要再手写 DCLP
- `std::call_once` 用于**绑定到外部 once_flag** 的初始化，不是函数级单例
- 看见 raw `new` 不配 `delete` 给一个进程级单例 → 泄漏（程序退出前不析构 → flush/cleanup 跑不到）
- 看见 `mutex` + `optional<T>` 实现 lazy → 想想 magic statics 能不能替

在 GCC/Clang/MSVC 上，magic statics 的实现是 Itanium ABI 规定的 `__cxa_guard_acquire / __cxa_guard_release`，fast path 是单次 acquire-load + branch（x86 上甚至是普通 load + branch，零额外指令）。性能远好于手写 mutex 方案。

注意：magic statics 解决"**当前函数被首次调用时构造**"——它**不解决** "static initialization order fiasco"（不同 TU 全局对象的构造顺序），那是另一个问题，用 "Construct On First Use" idiom 解（也是 magic statics）或 C++20 的 `constinit`（题5）。

**来源：** 手写题。magic statics 见 ISO/IEC 14882:2011 §6.7/4；DCLP 历史见 Scott Meyers & Andrei Alexandrescu "C++ and the Perils of Double-Checked Locking" (Dr. Dobb's, 2004)；C++11 之后的正解见 Herb Sutter "Use Lambdas for Private Implementation Details" / Meyers *Effective Modern C++* Item 16。
