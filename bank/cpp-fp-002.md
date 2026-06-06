---
qid: cpp-fp-002
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: B
---

# 认知：`typedef` 简化函数指针类型

用 `typedef` 为函数指针类型取别名，下列写法正确的是？（目标：`Comparator` 是"接受两个 `int`、返回 `bool`"的函数指针类型）

A. `typedef bool Comparator(int, int);`  
B. `typedef bool (*Comparator)(int, int);`  
C. `typedef (*Comparator)(int, int) bool;`  
D. `typedef bool* Comparator(int, int);`  
