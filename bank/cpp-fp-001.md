---
qid: cpp-fp-001
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: C
---

# 认知：函数指针声明语法

下列哪个声明正确地定义了一个"指向接受两个 `int` 参数、返回 `int` 的函数"的指针 `fp`？

A. `int fp(int, int)*;`  
B. `int* fp(int, int);`  
C. `int (*fp)(int, int);`  
D. `(*int) fp(int, int);`

## Explanation

正确答案是 C，对应“int (fp)(int, int);”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“int fp(int, int);”不满足题干要求；B 项“int fp(int, int);”不满足题干要求；D 项“(int) fp(int, int);”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
