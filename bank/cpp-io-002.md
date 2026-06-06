---
qid: cpp-io-002
type: single
kp: [cpp-io]
difficulty: easy
answer_key: C
---

# 认知：打开模式 app

以下哪个打开模式会将新写入内容**追加**到文件末尾，而不清空原有内容？

A. `ios::trunc`
B. `ios::out`
C. `ios::app`
D. `ios::in`

## Explanation

正确答案是 C，对应“ios::app”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“ios::trunc”不满足题干要求；B 项“ios::out”不满足题干要求；D 项“ios::in”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
