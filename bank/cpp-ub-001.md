---
qid: cpp-ub-001
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# 哪种操作属于未定义行为

下列哪种操作在 C++ 标准中明确属于**未定义行为（Undefined Behavior）**？

A. 将 `unsigned int` 加到最大值后再加 1（发生回绕）
B. 有符号整数 `int` 相加后超出 `INT_MAX`
C. 对空 `std::vector` 调用 `size()`，得到 0
D. 用 `static_cast<double>(42)` 将整数转为浮点数
