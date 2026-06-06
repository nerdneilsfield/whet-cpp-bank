---
qid: cpp-conc-hard-001
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: A
---

关于 `std::memory_order_seq_cst`，以下说法**正确**的是？

```cpp
std::atomic<int> x{0}, y{0};

// 线程1
x.store(1, std::memory_order_seq_cst);

// 线程2
y.store(1, std::memory_order_seq_cst);

// 线程3
int rx = x.load(std::memory_order_seq_cst);
int ry = y.load(std::memory_order_seq_cst);

// 线程4
int ry2 = y.load(std::memory_order_seq_cst);
int rx2 = x.load(std::memory_order_seq_cst);
```

A. 所有线程对 `seq_cst` 操作存在统一的全序，线程3看到 `rx=1, ry=0` 则线程4不可能看到 `ry2=1, rx2=0`
B. `seq_cst` 与 `acquire/release` 语义完全相同，只是性能更差
C. 线程3和线程4可能对 store 顺序产生相反的观测，因为多核缓存各自独立
D. `seq_cst` 只保证单个原子变量的读写不撕裂，不提供跨变量的顺序保证

## 解析

正确答案是 A。release/acquire 配对用于发布数据和获取数据，建立 happens-before 关系。选项 A 的表述“所有线程对 ｀seq_cst｀ 操作存在统一的全序，线程3看到 ｀rx=1, ry=0｀ 则线程4不可能看到 ｀ry2=1, rx2=0｀”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
