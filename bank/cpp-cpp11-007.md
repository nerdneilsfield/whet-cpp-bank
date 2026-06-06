---
qid: cpp-cpp11-007
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: A
---

# 认知：noexcept 的作用

标记函数为 `noexcept` 意味着什么？

A. 承诺该函数不会抛出异常；若抛出，程序调用 `std::terminate()`
B. 函数体内不允许出现 `throw` 关键字，否则编译失败
C. 函数抛出异常时会被自动捕获并忽略
D. 等同于 `throw()` 但仅在 C++11 之后可用，语义完全相同
