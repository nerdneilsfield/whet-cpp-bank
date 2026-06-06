---
qid: cpp-bp-concur-005
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: A
---

C++20 引入了 `std::latch` 和 `std::barrier`。下列哪个场景应当使用 `latch` 而不是 `barrier`？

```cpp
// 场景 A：主线程等待 N 个工作线程完成"初始化"，每个线程仅 count_down 一次
// 场景 B：N 个线程同步运行多轮 simulation，每轮结束都要互相等待

// 选项
// latch 用法
std::latch ready{N};
for (int i = 0; i < N; ++i) {
    std::thread([&]{ do_init(); ready.count_down(); }).detach();
}
ready.wait();   // 主线程

// barrier 用法
std::barrier sync{N};
for (int i = 0; i < N; ++i) {
    std::thread([&]{
        for (int round = 0; round < ROUNDS; ++round) {
            compute_round(round);
            sync.arrive_and_wait();    // 等所有线程都跑完这轮
        }
    }).detach();
}
```

A. 场景 A 用 latch，场景 B 用 barrier
B. 场景 A 用 barrier，场景 B 用 latch
C. 两者都用 latch
D. 两者都用 barrier

---

## 解析

C++20 引入两个互补的同步原语：

**`std::latch`** — 一次性闭锁：
- 构造时指定计数 N
- 任何线程可以 `count_down()` 减计数
- 计数到 0 后**永久打开**，所有 `wait()` 立刻返回
- **不可重置**

**`std::barrier`** — 可循环屏障：
- 构造时指定计数 N
- N 个线程都调用 `arrive_and_wait()` 后才一起通过
- 通过后**自动重置**为 N，可以再次循环使用
- 可以传入"completion 函数"在每轮结束时执行（如汇总数据）

判断准则：
- "等待一次性事件完成"（init 完成、shutdown 信号）→ **latch**
- "多轮迭代同步"（并行 simulation、并行算法的多阶段）→ **barrier**

场景 A 主线程等所有 worker 完成**一次性 init**，每个 worker 只 count_down 1 次，之后 worker 各自做别的事情 → **latch**

场景 B 多轮 simulation，每轮所有线程必须同步 → **barrier**

历史上 C++ 用 `condition_variable + counter + mutex` 手写这两类原语，复杂且易错。C++20 标准化后，应优先用：

```cpp
// 推荐
std::latch init_done{worker_count};
std::barrier round_sync{worker_count, []{ aggregate_round_stats(); }};
```

附：Boost.Thread、folly 等库早就有这两个原语，C++20 终于标准化。