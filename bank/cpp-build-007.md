---
qid: cpp-build-007
type: fill
kp: [cpp-build-tools]
difficulty: easy
answer_key: -g
---

# 题目

想用 gdb 对程序进行源码级调试，编译时必须加上 **___** 选项，使编译器在目标文件中嵌入行号、变量名等调试符号信息。

## 答案

`-g`。该选项让 gcc/clang 生成 DWARF 格式的调试信息。不加 `-g` 时，gdb 只能看到汇编，无法映射到源代码行。
