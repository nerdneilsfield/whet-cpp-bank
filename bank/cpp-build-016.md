---
qid: cpp-build-016
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: C
---

# 题目

下列关于 `gcc` 与 `g++` 区别的描述，哪一条是**正确**的？

A. `gcc` 和 `g++` 完全等价，可以任意互换
B. `gcc` 可以直接编译 C++ 代码，无需任何额外选项
C. `gcc` 默认以 C 模式处理 `.c` 文件；`g++` 默认以 C++ 模式处理，并自动链接 C++ 标准库
D. `g++` 是 gcc 的子集，功能比 gcc 少

## 选项解析

- A：不等价，链接阶段行为不同。
- B：`gcc` 编译 `.cpp` 时不会自动链接 `libstdc++`，C++ 特性可能链接失败。
- C：正确。`g++` 会自动添加 `-lstdc++` 等 C++ 运行时库，是编译 C++ 程序的推荐方式。
- D：`g++` 是 `gcc` 针对 C++ 的前端驱动，功能是超集而非子集。
