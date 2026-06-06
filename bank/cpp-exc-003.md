---
qid: cpp-exc-003
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: A
---

# C++ 异常处理：noexcept 说明符

以下关于 `noexcept` 的描述，**正确**的是？

A. `noexcept` 函数中若抛出异常，程序调用 `std::terminate()` 终止
B. `noexcept` 函数中若抛出异常，异常会被静默忽略
C. `noexcept` 函数编译时会报错，无法抛出异常
D. `noexcept` 等同于 `throw()`，两者完全相同

## Explanation

正确答案是 A。`noexcept` 是不抛异常承诺；异常若逃出该函数会调用 `std::terminate`。选项 A 的表述“｀noexcept｀ 函数中若抛出异常，程序调用 ｀std::terminate()｀ 终止”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
