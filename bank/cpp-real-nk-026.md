---
qid: cpp-real-nk-026
type: single
kp: [cpp-cpp11, cpp-cpp14-17]
primary_kp: cpp-cpp11
difficulty: medium
answer_key: B
tags: [interview-real, bytedance]
---

下列对 C++ 各版本新特性的归属，**错误**的是：

A. C++11：auto、lambda、智能指针、右值引用、`thread`/`mutex`/`atomic`
B. **C++14：concepts、modules、ranges、coroutines**
C. C++17：structured bindings、`if constexpr`、`std::optional`/`variant`/`any`、`std::filesystem`
D. C++20：concepts、modules、ranges、coroutines、三路比较运算符 `<=>`

---

**解析：**

B 错误，把 C++20 的特性归到了 C++14。

各版本主要特性时间线：

- **C++11** (2011): auto、lambda、智能指针、右值引用与移动语义、`std::thread`/`mutex`/`atomic`、范围 for 循环、`nullptr`、`enum class`、`constexpr`、可变参数模板
- **C++14** (2014): 泛型 lambda（`[](auto x){}`）、变量模板、`std::make_unique`、二进制字面量 `0b1010`
- **C++17** (2017): 结构化绑定、`if constexpr`、`if/switch` 初始化语句、折叠表达式、`std::optional`/`variant`/`any`/`string_view`、`std::filesystem`、并行算法
- **C++20** (2020): **四大金刚** concepts、modules、ranges、coroutines；`<=>` 三路比较、`consteval`、`constinit`、`std::format`

**来源：** 字节 C++ 面试题 / cppreference C++ 版本特性列表