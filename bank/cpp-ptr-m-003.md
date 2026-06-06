---
qid: cpp-ptr-m-003
type: multi
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: [A, D]
---

给定声明 `const int* p` 和 `int* const q`，下列哪些说法是正确的？（选择所有正确项）

A. `p` 是指向常量整数的指针，可以改变 `p` 本身的指向
B. `p` 是常量指针，不能改变 `p` 本身的指向
C. `q` 是指向常量整数的指针，可以通过 `*q = 5` 修改其值
D. `q` 是常量指针，不能改变 `q` 本身的指向，但可以通过 `*q = 5` 修改其指向的值
