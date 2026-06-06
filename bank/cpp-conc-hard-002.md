---
qid: cpp-conc-hard-002
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: B
---

以下代码使用 `release/acquire` 语义在两个线程间传递数据：

```cpp
std::atomic<bool> ready{false};
int data = 0;

// 线程1（生产者）
data = 42;                                        // (A)
ready.store(true, std::memory_order_release);     // (B)

// 线程2（消费者）
while (!ready.load(std::memory_order_acquire)) {} // (C)
assert(data == 42);                               // (D)
```

关于此代码，以下说法**正确**的是？

A. `data = 42` 和 `ready.store` 可能被重排，消费者读到 `ready=true` 时 `data` 仍可能为 0
B. `release` store 之前的所有写操作对 `acquire` load 成功之后的读操作可见，断言永远不会触发
C. 必须使用 `seq_cst` 才能保证 `data` 的可见性，`release/acquire` 不足以同步非原子变量
D. `while` 循环中的 `acquire` load 只保证循环内部的操作顺序，不影响循环之后的 `data` 读取

## Explanation

正确答案是 B。release/acquire 配对用于发布数据和获取数据，建立 happens-before 关系。选项 B 的表述“｀release｀ store 之前的所有写操作对 ｀acquire｀ load 成功之后的读操作可见，断言永远不会触发”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
