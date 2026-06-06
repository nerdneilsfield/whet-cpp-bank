---
qid: cpp-real-en-022
type: single
kp: [cpp-lambdas, cpp-cpp11]
primary_kp: cpp-lambdas
difficulty: medium
answer_key: B
tags: [interview-real, interviewbit]
---
关于 C++ lambda 表达式及其 capture clause（捕获子句），以下说法正确的是？

A. `[=]` 按值捕获时，捕获的变量在 lambda 内可以被直接修改
B. `[&]` 按引用捕获所有外部变量；`[=]` 按值捕获所有外部变量（副本，默认 const）
C. `mutable` 关键字可以让 lambda 修改按引用捕获的变量
D. 按值捕获的变量与外部原始变量共享同一份内存

---

**解析：**

- **按值捕获 `[=]`**：创建外部变量的副本存储在 lambda 对象中，默认 `const` 不可修改。如需修改需加 `mutable`。
- **按引用捕获 `[&]`**：捕获外部变量的引用，可以修改原始变量。
- **`mutable`**：使 lambda 的 `operator()` 成为非 const，从而允许修改按值捕获的副本。引用捕获的修改不需要 `mutable`（本来就是操作原变量）。
- 按值捕获的副本独立于原始变量，修改副本不影响原始变量。

```cpp
int x = 10;
auto l = [=]() mutable { x = 20; };  // 只修改副本
// 外部 x 仍然是 10
```

**来源：** InterviewBit "C++ Interview Questions" — Lambda Expressions