---
qid: cpp-build-013
type: fill
kp: [cpp-build-tools]
difficulty: easy
answer_key: -DDEBUG
---

# 题目

代码中有 `#ifdef DEBUG ... #endif` 块，希望在不修改源文件的情况下通过编译命令开启该块，应在编译命令中加上 **___** 选项。

## Explanation

`-DDEBUG`。`-D<宏名>` 等价于在源文件顶部写 `#define 宏名`。可带值：`-DVERSION=2` 等价于 `#define VERSION 2`。


答案是 `-DDEBUG`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。构建题要区分预处理、编译、汇编、链接以及编译选项、库路径和目标文件的职责。
