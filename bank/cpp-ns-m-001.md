---
qid: cpp-ns-m-001
type: multi
kp: [cpp-preprocessor]
difficulty: easy
answer_key: [A, C]
---

下列哪些方式可以**防止头文件被重复包含**？（选择所有正确项）

A. 在头文件首尾使用 `#ifndef MY_HEADER_H` / `#define MY_HEADER_H` / `#endif`
B. 在每个 `.cpp` 文件开头写 `#undef` 清除已有宏
C. 在头文件第一行写 `#pragma once`
D. 将所有函数实现写在 `.cpp` 文件中，头文件只保留声明
