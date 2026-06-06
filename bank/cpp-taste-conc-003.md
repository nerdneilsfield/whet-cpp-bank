---
qid: cpp-taste-conc-003
type: single
kp: [cpp-concurrency, cpp-classes]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: B
tags: [code-taste, best-practice]
---
要实现一个"线程安全的整数计数器，并附带最近一次修改的时间戳"。四个版本功能相同，哪个品味最好？

```cpp
// A
struct Counter_a {
    std::mutex mu;
    int value = 0;
    std::chrono::steady_clock::time_point last_update;

    void inc() {
        std::lock_guard lk(mu);
        ++value;
        last_update = std::chrono::steady_clock::now();
    }
};

// B
class Counter_b {
    struct State {
        int value = 0;
        std::chrono::steady_clock::time_point last_update;
    };
    mutable std::mutex mu_;
    State s_;
public:
    void inc() {
        std::lock_guard lk(mu_);
        ++s_.value;
        s_.last_update = std::chrono::steady_clock::now();
    }
    State snapshot() const {
        std::lock_guard lk(mu_);
        return s_;
    }
};

// C
struct Counter_c {
    std::atomic<int> value{0};
    std::atomic<long long> last_update_ns{0};

    void inc() {
        value.fetch_add(1, std::memory_order_relaxed);
        last_update_ns.store(
            std::chrono::steady_clock::now().time_since_epoch().count(),
            std::memory_order_relaxed);
    }
};

// D
class Counter_d {
    std::mutex value_mu_;
    std::mutex time_mu_;
    int value_ = 0;
    std::chrono::steady_clock::time_point last_update_;
public:
    void inc() {
        { std::lock_guard lk(value_mu_); ++value_; }
        { std::lock_guard lk(time_mu_);  last_update_ = std::chrono::steady_clock::now(); }
    }
};
```

A. A — 字段平铺 + 一把 mutex，最简单直接
B. B — 把"被保护的数据"打包成内嵌 struct，mutex 私有 + 暴露 const snapshot()
C. C — 两个 atomic 不用 mutex，最快
D. D — 两把锁粒度更细，并发度更高

---

**解析：**

选 B。这道题考 **"被保护数据应该和锁结构性绑定，且不向外泄露"**。

B 的关键品味在三处：

1. **把要一起保护的字段打包成 `State` 内嵌结构**——这一招立刻让"哪些字段共享同一把锁"在类型层面就可见。要再加一个字段（比如 `min_value`），写在 `State` 里、自动被同一把锁覆盖，不会有人忘记。
2. **`mutex` 私有 + `mutable`**——`mutable` 让 const 成员函数也能加锁（读也要加锁是线程安全的本质），私有保证外部无法绕过锁直接碰数据。
3. **`snapshot()` 返回 by value**——读者拿到的是**一致快照**（`value` 和 `last_update` 一定来自同一次锁内拷贝），不会读到一个改了一半的中间态。

逐一品味为什么其他版本不好：

- **A**：字段全 `public`、`mutex` 也是 `public`——外部代码可以直接 `c.value++` 绕过锁、也可以拿走 `mu` 在外面加锁形成隐藏耦合。封装失败。**且没有读接口**——别人要读 `value` 怎么办？外面加锁？那 `mu` 就泄露了；不加锁？那就是数据竞争。
- **C**：**两个独立 atomic ≠ 原子整体**。线程 1 inc 到 value=5、还没写 last_update_ns；线程 2 这时 snapshot 就会读到"value=5、时间戳是上一次"的不一致组合。`memory_order_relaxed` 进一步去掉了字段间的顺序保证。**atomic 只在单个变量的原子性上有用，多变量的不变式要靠锁**。这是把 atomic 当万能加速器的常见误用。
- **D**：**两把锁分别保护逻辑相关的两个字段是反模式**——既没提高并发（inc 仍然要拿两把锁，比一把更慢），又制造了和 C 一样的"读到不一致快照"风险。"细粒度锁"只对**独立的不变式**有意义，把同一个不变式拆开等于把数据完整性拆开。

**核心识别点：**

- 看见多个字段一起变更 → 它们属于**同一个不变式**，必须同一把锁
- 看见 `mutex` 是 `public` → 警觉封装泄漏
- 看见 const 成员函数要加锁 → 用 `mutable mutex`
- 看见两个 `atomic` 之间有逻辑约束 → 警觉，需要 mutex 而非 atomic
- 看见"细粒度锁"拆解同一组不变式 → 警觉，是不是该合并

把"被保护的数据 + 保护它的锁"作为一个**封装单元**是 Herb Sutter 反复提的设计原则——锁不是性能装饰，是数据不变式的物理边界。

**来源：** 手写题。结构性绑定原则见 Herb Sutter "Prefer to make member functions of classes that have mutable state thread-safe by default"；C++ Core Guidelines CP.20、CP.22；Anthony Williams *C++ Concurrency in Action* 2e §3.2 "Protecting shared data with mutexes"。
