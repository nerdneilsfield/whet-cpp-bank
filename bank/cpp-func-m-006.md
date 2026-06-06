---
qid: cpp-func-m-006
type: multi
kp: [cpp-functions]
difficulty: easy
answer_key: [A, B, C]
---

关于 C++ **`const` 引用参数**，选择所有正确项。

```cpp
void print(const std::string& s);
```

A. `const` 引用参数可以接受右值（临时对象）作为实参
B. `const` 引用参数既避免了拷贝，又防止函数修改实参
C. `const` 引用参数可以绑定到字面量，例如 `print("hello")`
D. `const` 引用参数与非 `const` 引用参数的函数可以构成重载，但调用时对非 const 对象会产生歧义错误

> 选择所有正确项。

## 解析

本题正确答案是 A, B, C。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。A 项正确：“const 引用参数可以接受右值（临时对象）作为实参”符合题干要求；B 项正确：“const 引用参数既避免了拷贝，又防止函数修改实参”符合题干要求；C 项正确：“const 引用参数可以绑定到字面量，例如 print("hello")”符合题干要求；D 项错误：“const 引用参数与非 const 引用参数的函数可以构成重载，但调用时对非 const 对象会产生歧义错误”与题干要求或 C++ 规则不符。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
