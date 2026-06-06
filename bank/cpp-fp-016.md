---
qid: cpp-fp-016
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: D
---

# 代码阅读：有捕获 lambda 不能赋给函数指针

```cpp
int base = 10;
int (*fp)(int) = [base](int x) { return x + base; };  // 行 A
```

行 A 的编译结果是？

A. 编译通过，`fp(5)` 返回 15  
B. 编译通过，但运行时崩溃  
C. 编译通过，捕获的 `base` 被忽略  
D. 编译错误：有捕获的 lambda 不能隐式转换为函数指针  
