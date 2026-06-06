---
qid: cpp-func-m-001
type: multi
kp: [cpp-functions]
difficulty: easy
answer_key: [A, C, D]
---

以下关于 C++ **函数重载**的条件，选择所有正确项。

```cpp
void foo(int x);
void foo(double x);
void foo(int x, int y);
```

A. 参数类型不同可以构成重载
B. 仅返回值类型不同可以构成重载
C. 参数数量不同可以构成重载
D. 参数的 `const` 修饰（顶层 const 除外）不同可以构成重载

> 选择所有正确项。

## Explanation

本题正确答案是 A, C, D。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。A 项正确：“参数类型不同可以构成重载”符合题干要求；B 项错误：“仅返回值类型不同可以构成重载”与题干要求或 C++ 规则不符；C 项正确：“参数数量不同可以构成重载”符合题干要求；D 项正确：“参数的 const 修饰（顶层 const 除外）不同可以构成重载”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
