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

## 解析

正确答案是 D，对应“编译错误：有捕获的 lambda 不能隐式转换为函数指针”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“编译通过，fp(5) 返回 15”不满足题干要求；B 项“编译通过，但运行时崩溃”不满足题干要求；C 项“编译通过，捕获的 base 被忽略”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
