---
qid: cpp-build-025
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: D
---

# 在 Makefile 中，`$(CC)` 和 `$(CXX)` 分别代表什么？

A. C 编译器路径 和 C 标准版本  
B. 编译标志 和 链接标志  
C. C 源文件列表 和 C++ 源文件列表  
D. C 编译器 和 C++ 编译器

## 解析

正确答案是 D。Makefile 中 `CC` 通常表示 C 编译器，`CXX` 表示 C++ 编译器；常见默认值分别是 `cc` 和 `g++` 或项目指定的编译器。编译选项通常放在 `CFLAGS`、`CXXFLAGS`、`LDFLAGS` 等变量中。
