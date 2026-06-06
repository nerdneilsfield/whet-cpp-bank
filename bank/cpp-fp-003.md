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
