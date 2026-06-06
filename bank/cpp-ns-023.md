---
qid: cpp-ns-023
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: D
---

下列关于 `#pragma once` 与 `#ifndef` 头文件保护的比较，说法正确的是？

A. `#pragma once` 是 C++ 标准强制要求的，所有编译器必须支持
B. `#ifndef` 方式更简洁，只需一行
C. `#pragma once` 不能与 `#ifndef` 同时出现在同一文件中
D. `#pragma once` 非标准但被主流编译器广泛支持；`#ifndef` 方式是 C++ 标准的一部分

## Explanation

正确答案是 D，因为该选项对应 ``#pragma once` 非标准但被主流编译器广泛支持；`#ifndef` 方式是 C++ 标准的一部分`，符合题中代码或概念的 C++ 语义。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 A 项、B 项、C 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
