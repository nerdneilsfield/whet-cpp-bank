---
qid: cpp-taste-conc-005
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: B
tags: [code-taste, best-practice]
---
一份"配置表"被大量线程频繁查询、偶尔由管理线程更新。四个版本功能相同，哪个品味最好？

```cpp
class Config {
    std::unordered_map<std::string, std::string> map_;
public:
    // A
    mutable std::mutex mu_a;
    std::string get_a(const std::string& key) const {
        std::lock_guard lk(mu_a);
        auto it = map_.find(key);
        return it == map_.end() ? "" : it->second;
    }
    void set_a(std::string k, std::string v) {
        std::lock_guard lk(mu_a);
        map_[std::move(k)] = std::move(v);
    }

    // B
    mutable std::shared_mutex mu_b;
    std::string get_b(const std::string& key) const {
        std::shared_lock lk(mu_b);
        auto it = map_.find(key);
        return it == map_.end() ? "" : it->second;
    }
    void set_b(std::string k, std::string v) {
        std::unique_lock lk(mu_b);
        map_[std::move(k)] = std::move(v);
    }

    // C
    mutable std::shared_mutex mu_c;
    std::string get_c(const std::string& key) const {
        std::unique_lock lk(mu_c);
        auto it = map_.find(key);
        return it == map_.end() ? "" : it->second;
    }
    void set_c(std::string k, std::string v) {
        std::unique_lock lk(mu_c);
        map_[std::move(k)] = std::move(v);
    }

    // D
    std::string get_d(const std::string& key) const {
        auto it = map_.find(key);
        return it == map_.end() ? "" : it->second;
    }
    void set_d(std::string k, std::string v) {
        map_[std::move(k)] = std::move(v);
    }
};
```

A. A — 一把 `mutex` 简单可靠，读写都用 `lock_guard`
B. B — `shared_mutex`：读用 `shared_lock`、写用 `unique_lock`，符合读多写少的场景
C. C — 用 `shared_mutex` 但 get 也加 `unique_lock`，更保守不易出错
D. D — 不用锁，让用户自己负责并发安全

---

**解析：**

选 B。这道题考 **"`shared_mutex` 的正确使用姿势 + 它适用的场景判断"**。

`std::shared_mutex`（C++17）的存在目的就是为了"**读远多于写**"的场景：多个 reader 可以同时持有 `shared_lock`，互不阻塞；writer 用 `unique_lock` 时排它持有。配置表正是教科书式的 reader-heavy 场景——B 的读路径没有任何线程间互斥开销（只有共享计数原子操作），写路径仍然独占。

逐一品味为什么其他版本不好：

- **A**：所有 reader 之间也互斥——10 个查询线程要排队一个一个进。在 reader 远多于 writer 时，吞吐被白白浪费。这是"用一把普通 mutex 一刀切"的保守写法，写得对但味道一般。**注意**：在写多读少 / 临界区极短的场景里，`mutex` 反而比 `shared_mutex` 更快（`shared_mutex` 内部计数+条件变量的开销不便宜）——所以 A 不是"错"，是"用错了场景"。
- **C**：**这是把 `shared_mutex` 当 `mutex` 用的反面教材**——用了一个比 `mutex` 更重的锁、却没享受任何并发读的好处，纯负优化。"保守"是个借口，实际是没理解 `shared_lock` / `unique_lock` 的区分意义。
- **D**：**直接的数据竞争**。`unordered_map` 的并发读写是 UB——即使所有线程都只是 `find`，只要有一个线程在 `set`，rehash 就可能让其他线程访问悬空 bucket。"让用户自己负责"是把并发安全推给调用方，违反了 RAII 时代"对象自己负责自己的不变式"的基本设计观。

**核心识别点：**

- 读远多于写 → `shared_mutex` + `shared_lock`（读） + `unique_lock`（写）
- 写多读少 / 临界区极短 → 普通 `mutex` 更快
- 看见 `shared_mutex` 配 `unique_lock` 读 → 警觉，是不是没分 reader/writer
- 看见任何"不加锁的共享可变容器" → 警觉数据竞争
- `shared_lock` 是 C++14 引入，`shared_mutex` 是 C++17（C++14 只有 `shared_timed_mutex`）

注意 B 的另一处品味：reader 拿到 `it->second` 后**返回 by value（拷贝）**，没有把引用泄露给外部——如果返回 `const std::string&`，调用方持有引用期间另一个线程写入触发 rehash 就崩了。这是一个隐藏品味点。

**来源：** 手写题。`shared_mutex` 适用场景见 C++ Core Guidelines CP.50；Anthony Williams *C++ Concurrency in Action* 2e §3.3.2；性能权衡见 Filip Pizlo "Locking in WebKit"。

## Explanation

正确答案是 B。这道题考 "`shared_mutex` 的正确使用姿势 + 它适用的场景判断"。
C：这是把 `shared_mutex` 当 `mutex` 用的反面教材——用了一个比 `mutex` 更重的锁、却没享受任何并发读的好处，纯负优化。
注意：在写多读少 / 临界区极短的场景里，`mutex` 反而比 `shared_mutex` 更快（`shared_mutex` 内部计数+条件变量的开销不便宜）——所以 A 不是"错"，是"用错了场景"。
