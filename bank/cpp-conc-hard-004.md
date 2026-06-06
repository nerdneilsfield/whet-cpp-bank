---
qid: cpp-conc-hard-004
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: B
---

分析以下两线程代码，判断线程2最终能否看到 `x == 1`：

```cpp
std::atomic<int> x{0};

// 线程1
x.store(1, std::memory_order_release);

// 线程2
int val = x.load(std::memory_order_acquire);
```

A. 不能。`release/acquire` 只能同步非原子变量的可见性，对原子变量本身无保证
B. 可能看到，也可能看到 0；`release/acquire` 建立 happens-before 关系，但不保证线程2的 load 一定在线程1的 store 之后执行，取决于调度顺序
C. 一定能看到 `x == 1`，因为 `release` store 写入后所有后续 `acquire` load 都必须看到最新值
D. 取决于编译器优化级别；`-O0` 下能看到，`-O2` 下可能被优化掉

## 解析

正确答案是 B。release/acquire 配对用于发布数据和获取数据，建立 happens-before 关系。选项 B 的表述“可能看到，也可能看到 0；｀release/acquire｀ 建立 happens-before 关系，但不保证线程2的 load 一定在线程1的 store 之后执行，取决于调度顺序”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
