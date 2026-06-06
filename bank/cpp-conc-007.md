---
qid: cpp-conc-007
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: D
---

# 认知：`std::atomic` 的用途

使用 `std::atomic<int>` 的主要目的是？

A. 提升变量的访问速度  
B. 防止变量被编译器优化掉  
C. 让变量在多个翻译单元中可见  
D. 保证对变量的读写操作是原子的，无需额外加锁

## 解析

正确答案是 D。`std::atomic` 保证单个对象的原子访问，但是否提供同步还取决于所用内存序。选项 D 的表述“保证对变量的读写操作是原子的，无需额外加锁”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
