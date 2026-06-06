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

## 解析

正确答案是 B，对应“typedef bool (Comparator)(int, int);”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“typedef bool Comparator(int, int);”不满足题干要求；C 项“typedef (Comparator)(int, int) bool;”不满足题干要求；D 项“typedef bool Comparator(int, int);”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
