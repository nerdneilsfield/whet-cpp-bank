---
qid: cpp-conc-hard-006
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: C
---

`compare_exchange_weak` 与 `compare_exchange_strong` 的核心区别是什么？以下说法**正确**的是？

A. `weak` 版本性能更差，因为它会多次重试直到成功；`strong` 版本只尝试一次
B. `weak` 版本只能用于 `bool` 类型，`strong` 版本支持所有整型
C. `weak` 版本在值确实匹配时也可能返回 `false`（伪失败），适合用在循环中；`strong` 版本不会伪失败，适合只执行一次的场合
D. 两者语义完全相同，仅编译器优化提示不同，实际行为无区别

```cpp
// weak 的惯用写法
std::atomic<int> val{0};
int expected = 0;
while (!val.compare_exchange_weak(expected, 1)) {
    expected = 0; // 重置 expected，处理伪失败和真失败
}

// strong 的惯用写法
bool ok = val.compare_exchange_strong(expected, 1);
// ok == false 则说明真正的竞争失败，无需循环
```
