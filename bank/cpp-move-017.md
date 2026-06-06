---
qid: cpp-move-017
type: multi
kp: [cpp-move-semantics]
difficulty: easy
answer_key: [A, C, D]
---

# 移动语义的优势场景

以下哪些场景中，移动语义相比拷贝语义有明显性能优势？（多选）

A. 将大型 `std::vector` 传入函数时使用 `std::move`
B. 对 `int` 类型变量使用 `std::move`
C. 从函数返回大型字符串（编译器可使用移动或 RVO）
D. 将 `std::unique_ptr` 转移所有权
E. 对 `char` 数组使用 `std::move`
