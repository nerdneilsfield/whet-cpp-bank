---
qid: cpp-real-nk-025
type: single
kp: [cpp-classes, cpp-templates]
primary_kp: cpp-classes
difficulty: easy
answer_key: D
tags: [interview-real, nowcoder]
---

C++ 中 `struct` 和 `class` 的区别**不包括**：

A. `struct` 成员默认是 public，`class` 默认是 private
B. `struct` 继承默认是 public，`class` 继承默认是 private
C. `class` 可以用作模板参数声明（`template<class T>`），早期 `struct` 不能
D. **`struct` 不能定义成员函数，`class` 才能**

---

**解析：**

D 错误。在 **C++** 中（不是 C），struct 和 class 几乎完全等价，区别仅在于：

1. **默认访问控制**：
   - struct 成员默认 public
   - class 成员默认 private

2. **默认继承方式**：
   - `struct D : Base` 默认 public 继承
   - `class D : Base` 默认 private 继承

3. **模板参数声明**：
   - 历史上 `template<class T>` 是唯一形式
   - C++17 起 `template<typename T>` 与之等价，且模板模板参数可用 `template<template<class> class>` 或 `typename`

C++ 的 struct **完全可以**定义成员函数、构造函数、析构函数、继承、虚函数、运算符重载等所有 class 能做的事。约定俗成 struct 用于 POD 类型，class 用于复杂封装。

**来源：** 牛客网 C++ 基础面试题 / cppreference