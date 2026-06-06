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

## Explanation

正确答案是 A。`noexcept` 是不抛异常承诺；异常若逃出该函数会调用 `std::terminate`。选项 A 的表述“承诺该函数不会抛出异常；若抛出，程序调用 ｀std::terminate()｀”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
