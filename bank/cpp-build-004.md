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
