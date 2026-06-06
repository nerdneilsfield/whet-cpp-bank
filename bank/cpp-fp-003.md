---
qid: cpp-fp-003
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: A
---

# 认知：`using` 简化函数指针类型

C++11 的 `using` 语法定义函数指针别名时，下列哪项等价于 `typedef void (*Handler)(int);`？

A. `using Handler = void (*)(int);`  
B. `using Handler = void (int);`  
C. `using Handler = (*void)(int);`  
D. `using void Handler(int);`

## 解析

正确答案是 A，对应“using Handler = void ()(int);”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：B 项“using Handler = void (int);”不满足题干要求；C 项“using Handler = (void)(int);”不满足题干要求；D 项“using void Handler(int);”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
