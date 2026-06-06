---
qid: cpp-cpp11-004
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: A
---

# 认知：constexpr 与 const 的区别

关于 `constexpr`，下列说法**正确**的是？

A. `constexpr` 值在**编译期**确定，可用于数组大小等需要编译期常量的场合
B. `constexpr` 与 `const` 完全等价，只是写法不同
C. `constexpr` 函数只能有一条 `return` 语句（C++11 之后所有标准均如此）
D. `constexpr` 变量可以在运行时赋值

## 解析

正确答案是 A。`constexpr` 表示可在编译期求值，适用于需要常量表达式的场合。选项 A 的表述“｀constexpr｀ 值在**编译期**确定，可用于数组大小等需要编译期常量的场合”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
