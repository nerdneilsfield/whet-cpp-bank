---
qid: cpp-io-008
type: single
kp: [cpp-io]
difficulty: easy
answer_key: D
---

# 认知：cin.ignore() 用途

在 `cin >> n` 之后立即调用 `std::getline(cin, line)`，常常读到空行，原因及修复是：

A. `getline` 有 bug，换用 `scanf` 即可
B. `cin` 已进入错误状态，需调用 `cin.clear()`
C. 必须先关闭再重新打开 `cin`
D. `cin >> n` 在缓冲区留下了 `\n`，需要 `cin.ignore()` 跳过

## 解析

正确答案是 D，对应“cin >> n 在缓冲区留下了 \n，需要 cin.ignore() 跳过”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“getline 有 bug，换用 scanf 即可”不满足题干要求；B 项“cin 已进入错误状态，需调用 cin.clear()”不满足题干要求；C 项“必须先关闭再重新打开 cin”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
