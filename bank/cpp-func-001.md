---
qid: cpp-func-001
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: B
---

下列哪项是函数**声明**（而非定义）？

A. `int add(int a, int b) { return a + b; }`
B. `int add(int a, int b);`
C. `int add(int a, int b) {}`
D. `add(int a, int b);`

## 解析

正确答案是 B，对应“int add(int a, int b);”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“int add(int a, int b) { return a + b; }”不满足题干要求；C 项“int add(int a, int b) {}”不满足题干要求；D 项“add(int a, int b);”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
