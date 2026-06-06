---
qid: cpp-func-m-004
type: multi
kp: [cpp-functions]
difficulty: easy
answer_key: [A, C, D]
---

关于 C++ **`inline` 函数**，选择所有正确项。

```cpp
inline int square(int x) {
    return x * x;
}
```

A. `inline` 是对编译器的建议，编译器可以忽略该请求
B. `inline` 函数保证每次调用都被展开，消除函数调用开销
C. `inline` 函数通常定义在头文件中，以便多个翻译单元使用
D. `inline` 函数在多个翻译单元中定义时，所有定义必须完全相同

> 选择所有正确项。

## Explanation

本题正确答案是 A, C, D。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。A 项正确：“inline 是对编译器的建议，编译器可以忽略该请求”符合题干要求；B 项错误：“inline 函数保证每次调用都被展开，消除函数调用开销”与题干要求或 C++ 规则不符；C 项正确：“inline 函数通常定义在头文件中，以便多个翻译单元使用”符合题干要求；D 项正确：“inline 函数在多个翻译单元中定义时，所有定义必须完全相同”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
