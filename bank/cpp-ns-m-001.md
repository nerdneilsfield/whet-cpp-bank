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

## 解析

正确答案是 A, C。A 项 `在头文件首尾使用 `#ifndef MY_HEADER_H` / `#define MY_HEADER_H` / `#endif`` 符合规则；C 项 `在头文件第一行写 `#pragma once`` 符合规则；B 项 `在每个 `.cpp` 文件开头写 `#undef` 清除已有宏` 不满足该规则；D 项 `将所有函数实现写在 `.cpp` 文件中，头文件只保留声明` 不满足该规则。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 多选题常见误区是只看关键字相似就勾选，而没有逐项检查它是否真的满足题干条件。
