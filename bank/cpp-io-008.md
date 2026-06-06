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
