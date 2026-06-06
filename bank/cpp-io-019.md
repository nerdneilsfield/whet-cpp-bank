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
