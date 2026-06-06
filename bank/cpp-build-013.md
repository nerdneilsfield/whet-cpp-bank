---
qid: cpp-build-013
type: fill
kp: [cpp-build-tools]
difficulty: easy
answer_key: -DDEBUG
---

# 题目

代码中有 `#ifdef DEBUG ... #endif` 块，希望在不修改源文件的情况下通过编译命令开启该块，应在编译命令中加上 **___** 选项。

## 答案

`-DDEBUG`。`-D<宏名>` 等价于在源文件顶部写 `#define 宏名`。可带值：`-DVERSION=2` 等价于 `#define VERSION 2`。
