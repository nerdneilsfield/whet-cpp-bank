---
qid: cpp-func-007
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: D
---

下列默认参数写法，哪个会导致编译错误？

A. `void f(int a, int b = 10);`
B. `void f(int a = 1, int b = 2);`
C. `void f(int a, int b = 5, int c = 6);`
D. `void f(int a = 1, int b);`

## Explanation

正确答案是 D，对应“void f(int a = 1, int b);”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“void f(int a, int b = 10);”不满足题干要求；B 项“void f(int a = 1, int b = 2);”不满足题干要求；C 项“void f(int a, int b = 5, int c = 6);”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
