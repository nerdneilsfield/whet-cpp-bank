---
qid: cpp-taste-conc-002
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: A
tags: [code-taste, best-practice]
---
账户转账需要同时持有两把 mutex（源账户 + 目标账户）。四个版本功能相同，哪一种品味最好？

```cpp
struct Account {
    std::mutex mu;
    int balance;
};

// A
void transfer_a(Account& from, Account& to, int amt) {
    std::scoped_lock lock(from.mu, to.mu);
    from.balance -= amt;
    to.balance   += amt;
}

// B
void transfer_b(Account& from, Account& to, int amt) {
    std::lock(from.mu, to.mu);
    std::lock_guard<std::mutex> l1(from.mu, std::adopt_lock);
    std::lock_guard<std::mutex> l2(to.mu,   std::adopt_lock);
    from.balance -= amt;
    to.balance   += amt;
}

// C
void transfer_c(Account& from, Account& to, int amt) {
    std::lock_guard<std::mutex> l1(from.mu);
    std::lock_guard<std::mutex> l2(to.mu);
    from.balance -= amt;
    to.balance   += amt;
}

// D
void transfer_d(Account& from, Account& to, int amt) {
    std::recursive_mutex rm;
    std::lock_guard<std::recursive_mutex> l(rm);
    from.balance -= amt;
    to.balance   += amt;
}
```

A. A — `scoped_lock` 一行原子加多把锁，C++17 最干净的写法
B. B — 用 `std::lock` + `adopt_lock` 是 C++11 的经典做法，最显基本功
C. C — 按声明顺序逐个 `lock_guard`，最朴实
D. D — 用 `recursive_mutex` 永远不会死锁，最稳

---

**解析：**

选 A。这道题考 **"多锁同时获取"的死锁规避**。

`std::scoped_lock` 不是 `lock_guard` 的变参重命名——它内部用 `std::lock` 算法（要么全部成功、要么全部回退）来获取所有锁，**保证没有循环等待死锁**。一行代码，意图清晰，零额外变量。

逐一品味：

- **B**：在 C++11 没有 `scoped_lock` 的年代，这是**唯一正确**的写法——先 `std::lock(a, b)` 用算法防死锁地拿到两把锁，再用 `adopt_lock` 标签让两个 `lock_guard` 接管已经持有的锁、负责析构时释放。**正确但啰嗦**——三行代码做一件事，C++17 之后已被 `scoped_lock` 一行取代。在新代码里继续用这个 idiom 是**没跟上标准库进化**。
- **C**：**致命错误是死锁**。线程 1 调 `transfer(A, B)`、线程 2 调 `transfer(B, A)`——线程 1 拿到 A.mu 等 B.mu、线程 2 拿到 B.mu 等 A.mu，**经典 ABBA 死锁**。按声明顺序加锁只在"全局总顺序"约定下才安全，而 `from`/`to` 是调用者决定的，没有全局顺序可言。
- **D**：**完全错位的工具**。`recursive_mutex` 解决的是"同一线程多次进入持有同一把锁"的问题（比如递归函数里反复 lock 同一个 mutex），它**根本不能跨 mutex 防死锁**。而且这里把 `rm` 写成函数内的 local 变量——每次调用都是一把新锁，**根本没保护任何东西**。两个错误叠加：选错锁类型 + 锁错位置。

**核心识别点：**

- 同时锁多把 mutex → `scoped_lock(m1, m2, ...)`（C++17）
- C++11 老代码里看见 `std::lock(a, b)` + `adopt_lock` → 知道这是 `scoped_lock` 之前的等价写法
- 看见**按顺序逐个 `lock_guard` 多把锁** → 警觉死锁
- 看见 `recursive_mutex` → 警觉是不是真有"同线程递归加锁"的合法需求，绝大多数 case 是设计错误
- 看见 mutex 是 **local 变量** → 警觉，mutex 必须和被保护数据同生命周期

A 选项的写法不只是"少打几行字"——它把"原子加多锁"这一抽象**封装在类型本身**里，连 `adopt_lock` 标签都不用提，意图直接由构造函数表达。这是 C++17 给并发代码的一个标志性改进。

**来源：** 手写题。`scoped_lock` 规范见 ISO/IEC 14882:2017 §33.4.4.2 [thread.lock.scoped]；ABBA 死锁与多锁同时获取见 Anthony Williams *C++ Concurrency in Action* 2e §3.2.4；`recursive_mutex` 的设计原则见 Herb Sutter "Use threads correctly = isolation + asynchronous messages"。

## Explanation

正确答案是 A。正确但啰嗦——三行代码做一件事，C++17 之后已被 `scoped_lock` 一行取代。
这道题考 "多锁同时获取"的死锁规避。
`std::scoped_lock` 不是 `lock_guard` 的变参重命名——它内部用 `std::lock` 算法（要么全部成功、要么全部回退）来获取所有锁，保证没有循环等待死锁。
