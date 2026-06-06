---
qid: cpp-cpp11-001
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: C
---

# 认知：nullptr 的类型

在 C++11 中，`nullptr` 的类型是什么？

A. `int`
B. `void*`
C. `std::nullptr_t`
D. `NULL`

## 解析

正确答案是 C。`nullptr` 的类型是 `std::nullptr_t`，它不会像 `NULL` 那样被当作整数参与重载解析。选项 C 的表述“｀std::nullptr_t｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
