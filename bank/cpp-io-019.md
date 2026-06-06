---
qid: cpp-io-019
type: multi
kp: [cpp-io]
difficulty: easy
answer_key: [B, C]
---

# 代码阅读：格式化输出头文件

下列哪些操纵符需要包含 `<iomanip>` 才能使用？（多选）

A. `std::endl`
B. `std::setw(10)`
C. `std::setprecision(3)`
D. `std::fixed`
E. `std::hex`

> `endl`、`fixed`、`hex` 定义在 `<ios>` / `<ostream>`（随 `<iostream>` 引入）；`setw` 和 `setprecision` 定义在 `<iomanip>`。

## 解析

本题正确答案是 B, C。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。A 项错误：“std::endl”与题干要求或 C++ 规则不符；B 项正确：“std::setw(10)”符合题干要求；C 项正确：“std::setprecision(3)”符合题干要求；D 项错误：“std::fixed E. std::hex”与题干要求或 C++ 规则不符。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
