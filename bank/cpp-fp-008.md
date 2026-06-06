---
qid: cpp-fp-008
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: C
---

# 认知：`std::function` 与函数指针的性能权衡

与裸函数指针相比，`std::function` 的主要代价是？

A. `std::function` 只能在堆上分配，开销来自内存泄漏风险  
B. `std::function` 不支持内联，但没有其他额外开销  
C. `std::function` 有类型擦除和潜在堆分配的运行时开销，调用时通常无法内联  
D. `std::function` 比函数指针快，因为它做了编译器优化

## 解析

正确答案是 C，对应“std::function 有类型擦除和潜在堆分配的运行时开销，调用时通常无法内联”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“std::function 只能在堆上分配，开销来自内存泄漏风险”不满足题干要求；B 项“std::function 不支持内联，但没有其他额外开销”不满足题干要求；D 项“std::function 比函数指针快，因为它做了编译器优化”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
