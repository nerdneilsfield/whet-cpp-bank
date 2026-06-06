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

## Explanation

正确答案是 A、C、D。大型 `vector`、大型字符串返回以及 `unique_ptr` 所有权转移都能避免昂贵拷贝或实现只能移动的语义。B 中 `int` 很小，移动与拷贝无性能差异；E 中裸数组表达式不能通过 `std::move` 自动转移底层数组内容。
