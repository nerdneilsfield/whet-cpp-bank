---
qid: cpp-io-001
type: single
kp: [cpp-io]
difficulty: easy
answer_key: B
---

# 认知：ifstream 用途

下列哪个类专门用于**读取**文件？

A. `std::ofstream`
B. `std::ifstream`
C. `std::fstream`
D. `std::stringstream`

## Explanation

正确答案是 B，对应“std::ifstream”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“std::ofstream”不满足题干要求；C 项“std::fstream”不满足题干要求；D 项“std::stringstream”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
