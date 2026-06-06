---
qid: cpp-taste-conc-008
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: B
tags: [code-taste, best-practice]
---
要写一个全局的 `Logger&` 单例 getter，第一次调用时构造，且要线程安全。四个版本功能相同，哪个品味最好？

```cpp
class Logger { /* heavy ctor */ };

// A
Logger& get_a() {
    static std::once_flag flag;
    static Logger* p = nullptr;
    std::call_once(flag, []{ p = new Logger(); });
    return *p;
}

// B
Logger& get_b() {
    static Logger instance;
    return instance;
}

// C
Logger& get_c() {
    static std::mutex mu;
    static Logger* p = nullptr;
    std::lock_guard lk(mu);
    if (!p) p = new Logger();
    return *p;
}

// D
Logger& get_d() {
    static std::atomic<Logger*> p{nullptr};
    Logger* tmp = p.load(std::memory_order_acquire);
    if (!tmp) {
        static std::mutex mu;
        std::lock_guard lk(mu);
        tmp = p.load(std::memory_order_relaxed);
        if (!tmp) {
            tmp = new Logger();
            p.store(tmp, std::memory_order_release);
        }
    }
    return *tmp;
}
```

A. A — `std::call_once` 是为"恰好执行一次"专门设计的工具，最贴语义
B. B — 函数内 static 变量，C++11 保证线程安全初始化，最简洁
C. C — 老老实实加锁判空，最易理解
D. D — 双重检查锁定（DCLP）+ atomic，C++11 之后唯一正确的高性能写法

---

**解析：**

选 B。这道题考 **"function-local static (Meyers Singleton) 的 C++11 保证"**——大部分人**不知道这条标准条款**，会去找更复杂的方案。

C++11 起 [stmt.dcl] 明确规定：**function-local static 变量的初始化是线程安全的**——如果多个线程同时进入 `get_b()` 第一次，编译器保证只有一个线程执行构造、其他线程等待；后续调用直接返回引用，零同步开销（fast path 只是一次原子标志位读取，被分支预测吃掉）。这就是 Scott Meyers 的 "Meyers Singleton"。**一行代码搞定全部需求**——线程安全初始化 + 自动销毁（程序退出时按构造逆序析构）+ 无堆分配。

逐一品味：

- **A**：`call_once` 设计目标确实是"恰好执行一次"，本身没错。但用在单例 getter 上 (1) 比 B 多了一个 `once_flag`、一个 `new`、一个原始指针；(2) **泄漏了 Logger**——`new` 出来再也没 delete，程序退出时不调析构（虽然进程退出时 OS 回收内存，但析构函数里的 flush 日志 / 关闭文件不会执行）；(3) 多写 3 行代码做 B 一行做的事。`call_once` 真正用武之地是"初始化逻辑分布在多处、和构造不绑定"的场景。
- **C**：每次调用都加锁——**fast path 也付锁的开销**。在高频日志场景里这是性能灾难。"最易理解"是错觉，"理解后再写就够好"才是品味。
- **D**：**这是经典反面教材**。Scott Meyers 和 Andrei Alexandrescu 2004 年的著名论文 "C++ and the Perils of Double-Checked Locking" 详细论证了 DCLP 在 C++11 之前根本写不对（没有标准内存模型）。C++11 之后用 atomic + acquire/release 理论上能写对，**但 (1) 代码极其复杂，95% 的人写错；(2) 性能比 B 没快——B 的 fast path 已经是单次原子读了**。"我会写 DCLP"在 C++11 之后是炫技不是品味——标准已经免费给你正确的实现，没必要自己再造。

**核心识别点：**

- 函数内单例 → `static Local instance; return instance;`（Meyers Singleton）
- 全局 `Logger*` + `call_once` → 警觉是不是不知道 function-local static
- 看见 DCLP 手写 → 警觉，在 C++11 之后是过度工程
- 单例 `new` 出来不 delete → 警觉析构副作用丢失
- "every call 加锁" → 警觉 fast path 开销

C++11 这条 [stmt.dcl] 保证（俗称 "magic statics"）是标准给单例模式的官方解决方案——所有 C++ 教材在讲单例时都会提，但工程师圈仍有大量"我觉得不安全所以自己加锁"的过度防卫式代码。**信任标准、读标准**是味道的根。

**来源：** 手写题。Magic statics 见 ISO/IEC 14882:2011 §6.7/4；DCLP 历史见 Meyers & Alexandrescu "C++ and the Perils of Double-Checked Locking" (Dr. Dobb's 2004)；Meyers Singleton 见 Scott Meyers *Effective C++* 3e Item 4。

## Explanation

正确答案是 B。"我会写 DCLP"在 C++11 之后是炫技不是品味——标准已经免费给你正确的实现，没必要自己再造。
C++11 起 [stmt.dcl] 明确规定：function-local static 变量的初始化是线程安全的——如果多个线程同时进入 `get_b()` 第一次，编译器保证只有一个线程执行构造、其他线程等待；后续调用直接返回引用，零同步开销（fast path 只是一次原子标志位读取，被分支预测吃掉）。
逐一品味： A：`call_once` 设计目标确实是"恰好执行一次"，本身没错。
