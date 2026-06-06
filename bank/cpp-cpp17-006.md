---
qid: cpp-cpp17-006
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: C
---

# 认知：C++14 泛型 lambda

C++14 引入了泛型 lambda，下列哪种写法使用了该特性？

A. `auto f = [](int x) { return x * 2; };`
B. `auto f = []<typename T>(T x) { return x; };`
C. `auto f = [](auto x) { return x * 2; };`
D. `template<> auto f = [](int x) { return x; };`

## 解析

正确答案是 C。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 C 的表述“｀auto f = [](auto x) { return x * 2; };｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
