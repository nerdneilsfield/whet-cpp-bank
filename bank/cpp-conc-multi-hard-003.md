---
qid: cpp-conc-multi-hard-003
type: multi
kp: [cpp-concurrency]
difficulty: hard
answer_key: [A, B, C]
---
关于 C++ 内存模型中的 happens-before 关系，以下说法正确的是哪些？

```cpp
std::atomic<int> flag{0};
int data = 0;

// Thread A
data = 42;
flag.store(1, std::memory_order_release);

// Thread B
while (flag.load(std::memory_order_acquire) != 1) { }
int read = data;   // read 一定是 42 吗？
```

A. Thread A 的 `flag.store(release)` 与 Thread B 的 `flag.load(acquire)` 在同一个原子变量上形成同步（synchronize-with）关系。
B. 因此 Thread A 中 `data = 42` sequenced-before `flag.store`，而 `flag.store` synchronizes-with `flag.load`，`flag.load` sequenced-before `read = data`。由三者传递构成 happens-before，保证了 `read == 42`。
C. inter-thread happens-before 由同步关系传递得到；同一个线程内由 sequenced-before 自然构成。
D. 如果两个线程之间没有形成任何同步关系，那么读取另一个线程写入的非原子变量仍然是安全的——编译器会确保不出现 TOCTOU 问题。

---

**解析：**

A 正确：release 和 acquire 在同一个原子变量上形成同步关系（synchronizes-with），这是 C++ 内存模型的最基本同步设施。
B 正确：sequenced-before + synchronizes-with 可以传递构造 inter-thread happens-before，这正是 release-acquire 模式下数据可见性的保障链。
C 正确：happens-before 分为同一线程内的 sequenced-before 和跨线程的"由同步关系传递"两部分，这之间可以传递，正是标准中定义的 happens-before 关系。
D 错误：在没有同步关系的条件下读取其他线程写入的非原子变量是**数据竞争**（data race），属于未定义行为。C++ 标准不保证任何可见性或顺序，不是"仍然安全"。

## Explanation

A、B、C 正确：release store 与同一原子变量上的 acquire load 可形成 synchronizes-with 关系。线程内的 sequenced-before 与跨线程同步关系传递后形成 happens-before，从而保证普通数据写入对读取线程可见。常见误区是认为没有同步的普通变量读写也只是“读到旧值”；实际上并发读写普通变量是数据竞争和 UB。
