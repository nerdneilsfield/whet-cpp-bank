---
qid: cpp-cpp11-med-001
type: single
kp: [cpp-cpp11]
difficulty: medium
answer_key: B
---

`auto` 与 `decltype` 对于同一个表达式 `x` 的推导结果可能不同。对于以下代码，`a` 和 `b` 的类型分别是？

```cpp
const int ci = 42;
const int& cri = ci;
auto a = cri;
decltype(cri) b = ci;
```

A. `a` 是 `int`，`b` 是 `const int&`
B. `a` 是 `int`，`b` 是 `const int&`
C. `a` 是 `const int&`，`b` 是 `const int&`
D. `a` 是 `const int`，`b` 是 `int`

---

**解析：**

`auto` 进行模板式推导：忽略引用和顶层 cv，所以 `cri` 被推导为 `int`（值类型）。`decltype` 保留引用性和 cv：对于变量名直接使用，`decltype(cri)` 就是 `const int&`。

这是 C++11 引入 `auto` 和 `decltype` 的核心区别之一，也是后续 `decltype(auto)` 诞生的原因。