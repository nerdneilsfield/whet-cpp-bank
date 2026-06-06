---
qid: cpp-bp-multi-med-003
type: multi
kp: [cpp-concurrency]
difficulty: medium
answer_key: [A, C, D]
---
关于 C++ 中的数据竞争（data race）条件，**哪些场景是数据竞争，哪些不是**？（多选）

```cpp
std::atomic<int> ai{0};
int plain = 0;
```

A. 线程 1：`plain = 1;` 线程 2：`int x = plain;`（无任何同步，同一非原子非互斥变量的并发读写）——**是**数据竞争
B. 线程 1：`ai.store(1, std::memory_order_relaxed);` 线程 2：`int x = ai.load(std::memory_order_relaxed);`——**是**数据竞争
C. 线程 1：`ai.store(1);` 线程 2：`ai.store(2);` 并发写同一原子变量——**不是**数据竞争（没有读写冲突到未定义行为）
D. 线程 1：`std::lock_guard lk(m); plain = 1;` 线程 2：`std::lock_guard lk(m); int x = plain;`——**不是**数据竞争（互斥量保护）

---

**解析：**

A 正确：同一非原子普通变量的并发读+写（无任何同步）是标准定义的数据竞争——未定义行为。
B 错误：原子变量的 `relaxed` load/store 仍然是原子的，不构成数据竞争。`relaxed` 仅不保证顺序一致性，但单次访问原子性保证。因此这不是数据竞争。
C 正确：两个线程并发写同一原子变量是合法的（结果正确地为其中一个值），不是数据竞争。
D 正确：互斥量保证了 `plain` 的读写在临界区内的互斥性，这是正确同步的，不是数据竞争。