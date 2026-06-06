---
qid: cpp-tmpl-multi-hard-001
type: multi
kp: [cpp-templates]
difficulty: hard
answer_key: [A, C, D]
---
关于 SFINAE 与 C++20 concepts 的区别，以下说法正确的是哪些？

```cpp
template<typename T>
auto f(T t) -> decltype(t.foo(), void()) { }   // (1) SFINAE

template<typename T>
requires requires(T t) { t.foo(); }
void g(T t) { }                                  // (2) concept
```

A. 当 `T` 没有 `foo()` 时，(1) 和 (2) 都会让重载解析把该候选静默剔除，而不是产生硬错误。
B. SFINAE 与 concepts 在错误诊断信息质量上完全一致，编译器报错内容没有实质差别。
C. concepts 参与重载排序（subsumption），可以根据约束的"更特化"关系自动选择最佳重载；SFINAE 不能。
D. concepts 检查发生在模板实参替换之前的约束求值阶段，可避免 SFINAE 中"替换深度过深"导致硬错误的情形。

---

**解析：**

A 正确：SFINAE 的核心规则就是"替换失败不是错误"，候选会被静默剔除；concepts 在约束不满足时同样不会让该候选成为可行重载，重载解析行为一致。
B 错误：concepts 的诊断信息明显优于 SFINAE。concepts 直接报告"约束 X 未满足"，而 SFINAE 失败往往给出长串的"no matching function"+候选列表，可读性差很多，这是 concepts 的主要卖点之一。
C 正确：concepts 之间存在 subsumption（包含）关系，编译器能据此对重载/特化排序，自动选择约束更强（更特化）的版本，SFINAE 无此机制，必须靠 tag dispatch 或 `std::enable_if` 互斥条件人工区分。
D 正确：concepts 的约束在替换前作为布尔表达式求值，只检查表达式合法性而不实例化整个函数体，因此能避免 SFINAE 中因深层实例化而触发的硬错误（即所谓 immediate context 之外的失败）。

## Explanation

A、C、D 正确：SFINAE 和 concepts 都能让不满足条件的候选退出重载解析，但 concepts 的约束表达更清晰、诊断更好。Concepts 还能参与约束的 subsumption 排序，自动选择更特化的重载。常见误区是把 concepts 只看作 `enable_if` 的语法糖，忽略其约束模型和错误诊断优势。
