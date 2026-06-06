---
qid: cpp-cpp11-short-001
type: short
kp: [cpp-cpp11]
difficulty: medium
rubric:
  - 区分 auto：根据初始化表达式推导变量类型（编译期）
  - 区分 decltype(expr)：得到表达式的精确类型（不求值），保留引用与 cv 限定
  - 给出例子：`auto x = vec[0]; // T` vs `decltype(vec[0]) y = vec[0]; // T&`
  - 提到 decltype(auto) 用于按 decltype 规则推导
---
请说明 C++11 中的 `auto` 和 `decltype` 的区别，并各举一个例子。

---

**参考答案：**

`auto` 用于变量声明时根据初始化表达式推导类型，遵循模板参数推导规则——会忽略顶层 const 与引用（`auto x = vec[0];` 推导为元素值类型而非引用）。`decltype(expr)` 在编译期得到表达式的精确类型而不求值，会保留引用、cv 限定符（`decltype(vec[0])` 通常是 `T&`）。结合 `decltype(auto)`（C++14）可让变量声明也使用 decltype 规则推导，常用于完美转发返回值场景。简言之，`auto` 适合写"我想要个值"，`decltype` 适合需要精确类型签名时使用。

## 解析

`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。 本题短答应围绕核心概念展开：｀auto｀ 用于变量声明时根据初始化表达式推导类型，遵循模板参数推导规则——会忽略顶层 const 与引用（｀auto x = vec[0];｀ 推导为元素值类型而非引用）。｀decltype(expr)｀ 在编译期得到表达式的精确类型而不求值，会保留引用、cv 限定符（｀decltype(vec[0])｀ 通常是 ｀T&｀）。结合 ｀decltype(auto)｀（C++14）可让变量声明也使用 decltype 规则推导，常用于完美转发返回值场景。简言之，｀auto｀ 适合写"我想要个值"，｀decltype 评分重点包括：区分 auto：根据初始化表达式推导变量类型（编译期）；区分 decltype(expr)：得到表达式的精确类型（不求值），保留引用与 cv 限定；给出例子：`auto x = vec[0]; // T` vs `decltype(vec[0]) y = vec[0]; // T&`。常见误区是只给出结论、不说明机制，或忽略异常路径、同步边界、生命周期等限制条件。
