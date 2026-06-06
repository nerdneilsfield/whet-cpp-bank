---
qid: cpp-build-017
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: A
---

# 题目

关于 clang 与 gcc 的命令行兼容性，以下哪条描述最准确？

A. clang/clang++ 与 gcc/g++ 共享绝大多数常用选项（`-O2`、`-Wall`、`-std`、`-I`、`-L` 等），可以在大多数项目中直接替换
B. clang 只支持 C，不支持 C++
C. clang 的优化选项与 gcc 完全不同，无法共用 Makefile
D. clang 不支持 `-g` 调试信息选项

## Explanation

- A：正确。clang 刻意保持与 gcc 的选项兼容，大量项目只需将 `CC=gcc` 改为 `CC=clang` 即可切换。
- B：clang++ 是 clang 的 C++ 前端，完全支持 C++。
- C：常用优化选项（`-O0`～`-O3`）clang 与 gcc 相同。
- D：clang 完整支持 `-g`，生成的也是 DWARF 格式调试信息。


正确答案为 A，因为“clang/clang++ 与 gcc/g++ 共享绝大多数常用选项（`-O2`、`-Wall`、`-std`、`-I`、`-L` 等），可以在大多数项目中直接替换”符合题干所问的 C++ 规则或代码执行结果。B、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。构建题要区分预处理、编译、汇编、链接以及编译选项、库路径和目标文件的职责。
