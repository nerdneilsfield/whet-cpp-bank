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
