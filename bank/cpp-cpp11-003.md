---
qid: cpp-cpp11-003
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: D
---

# 认知：auto 推导规则

下列关于 `auto` 的说法，**正确**的是哪一条？

A. `auto` 变量必须在函数返回类型处使用
B. `auto` 不能推导引用类型
C. `auto x = 1;` 推导出 `x` 为 `long`
D. `auto x = 1;` 推导出 `x` 为 `int`

## Explanation

正确答案是 D。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 D 的表述“｀auto x = 1;｀ 推导出 ｀x｀ 为 ｀int｀”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
