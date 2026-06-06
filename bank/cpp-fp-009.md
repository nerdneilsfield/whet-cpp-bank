---
qid: cpp-fp-009
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: B
---

# 代码阅读：函数指针赋值与调用

```cpp
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int (*fp)(int, int) = add;
fp = sub;
int result = fp(10, 3);
```

`result` 的值是？

A. 13  
B. 7  
C. 编译错误  
D. 未定义行为

## 解析

正确答案是 B，对应“7”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“13”不满足题干要求；C 项“编译错误”不满足题干要求；D 项“未定义行为”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
