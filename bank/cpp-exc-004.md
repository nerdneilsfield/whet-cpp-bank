---
qid: cpp-exc-004
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: B
---

# C++ 异常处理：std::exception 层级

`std::runtime_error` 和 `std::logic_error` 的共同基类是？

A. `std::bad_exception`
B. `std::exception`
C. `std::error`
D. `std::base_error`

## 解析

正确答案是 B。标准异常层次通常以 `std::exception` 为公共基类，并通过 `what()` 返回说明。选项 B 的表述“｀std::exception｀”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
