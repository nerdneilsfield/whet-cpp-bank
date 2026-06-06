---
qid: cpp-build-009
type: fill
kp: [cpp-build-tools]
difficulty: easy
answer_key: -std=c++17
---

# 题目

要让 g++ 按照 C++17 标准编译代码（启用结构化绑定、`if constexpr` 等特性），编译命令中应加上 **___** 选项。

## 答案

`-std=c++17`。类似地，C++14 用 `-std=c++14`，C++20 用 `-std=c++20`。不指定时 gcc 默认使用较旧的标准（通常 gnu++14 或 gnu++17，视版本而定）。
