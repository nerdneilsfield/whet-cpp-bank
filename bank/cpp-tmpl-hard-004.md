---
qid: cpp-tmpl-hard-004
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: C
---

对比 SFINAE 与 C++20 concepts，下列说法最准确的是？

```cpp
// SFINAE
template<typename T>
auto f(T t) -> std::enable_if_t<std::is_integral_v<T>, void> { /* ... */ }

// concepts
template<std::integral T>
void g(T t) { /* ... */ }
```

A. concepts 只是 SFINAE 的语法糖，编译产物完全相同
B. SFINAE 在不满足条件时报错信息更清晰
C. concepts 提供短路求值、更友好的诊断信息、支持基于约束包含关系的偏序重载决议（更具特化的约束优先）；SFINAE 仅是"替换失败不是错误"，无法表达"哪些约束彼此蕴含"
D. concepts 只能用于类模板参数，不能用于函数

## 解析

C++20 concepts 相对 SFINAE 的核心改进：(1) 表达直观：`requires` 子句直接写出约束；(2) 诊断显著友好（不再有数十屏的"substitution failure"）；(3) **约束包含（subsumption）**：编译器能分析两个 concept 间的逻辑蕴含关系，从而在多个候选模板中选择"约束更强"的版本，实现更精细的偏序重载——这是 SFINAE 几乎做不到的。例如 `integral` ⊆ `regular`，则同时满足两者时，选用 `integral` 版本。SFINAE 只能逐条独立判断"满足或不满足"，无法表达约束间的层次。B 错误：SFINAE 错误极差；D 错误：concepts 通用。