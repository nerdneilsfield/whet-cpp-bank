---
qid: cpp-build-004
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: A
---

# 题目

以下哪条命令只将 `main.cpp` 编译并汇编成目标文件，**不**进行链接？

A. `g++ -c main.cpp`
B. `g++ -S main.cpp`
C. `g++ -E main.cpp`
D. `g++ main.cpp`

## 选项解析

- A：正确。`-c` 表示"compile only"，输出 `main.o`，不链接。
- B：`-S` 停在汇编阶段，输出 `.s` 汇编文本，还没到目标文件。
- C：`-E` 只做预处理，输出宏展开后的源文本。
- D：完整流程，最终产生可执行文件。

## 解析

正确答案为 A，因为“`g++ -c main.cpp`”符合题干所问的 C++ 规则或代码执行结果。B、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。构建题要区分预处理、编译、汇编、链接以及编译选项、库路径和目标文件的职责。
