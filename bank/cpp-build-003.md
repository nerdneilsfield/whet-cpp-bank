---
qid: cpp-build-003
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: C
---

# 题目

执行 `g++ -S hello.cpp` 后，会在当前目录生成哪个文件？

A. `hello.i`
B. `hello.o`
C. `hello.s`
D. `hello`（可执行文件）

## 选项解析

- A：`-E` 选项才停在预处理，产物为 `.i`。
- B：`-c` 选项才停在汇编，产物为 `.o`。
- C：正确。`-S` 只进行到汇编阶段，输出文件是人类可读的汇编代码 `.s`。
- D：不带任何停止选项才会继续到链接，产生可执行文件。
