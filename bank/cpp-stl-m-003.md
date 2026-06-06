---
qid: cpp-stl-m-003
type: multi
kp: [cpp-stl-basics]
difficulty: easy
answer_key: [B, C]
---

关于 `std::endl` 与 `"\n"` 的区别，下列哪些说法正确？（选择所有正确项）

A. `std::endl` 与 `"\n"` 完全等价，性能相同
B. `std::endl` 会在输出换行符后额外刷新（flush）输出缓冲区
C. 在性能敏感的循环中，使用 `"\n"` 通常比 `std::endl` 更快
D. `"\n"` 会自动刷新标准输出缓冲区
