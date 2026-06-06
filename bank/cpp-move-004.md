---
qid: cpp-move-004
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: B
---

# std::move 的作用

`std::move(x)` 的实际效果是？

A. 立即将 x 的内容移动到另一个对象
B. 将 x 转换为右值引用，使后续操作可以调用移动语义
C. 销毁 x 并释放其内存
D. 复制 x 的值到一个临时对象
