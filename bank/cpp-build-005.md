---
qid: cpp-build-005
type: fill
kp: [cpp-build-tools]
difficulty: easy
answer_key: -o
---

# 题目

`g++ main.cpp _____ myprog` 中，下划线处应填写哪个选项，才能将输出的可执行文件命名为 `myprog` 而不是默认的 `a.out`？

## 答案

`-o`。`-o <文件名>` 用于指定编译输出文件的名称，适用于可执行文件、目标文件等所有输出类型。
