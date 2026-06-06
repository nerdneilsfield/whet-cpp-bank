---
qid: cpp-cpp17-001
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: B
---

# 认知：结构化绑定的语法

下列哪种写法是 C++17 结构化绑定的正确语法？

A. `auto a, b = std::make_pair(1, 2);`
B. `auto [a, b] = std::make_pair(1, 2);`
C. `auto (a, b) = std::make_pair(1, 2);`
D. `let [a, b] = std::make_pair(1, 2);`

## 解析

正确答案是 B。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 B 的表述“｀auto [a, b] = std::make_pair(1, 2);｀”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
