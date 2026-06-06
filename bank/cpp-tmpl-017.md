---
qid: cpp-tmpl-017
type: multi
kp: [cpp-templates]
difficulty: easy
answer_key: [B, D]
---

# 函数模板类型推导规则

```cpp
template<typename T>
void f(T x);
```

下列调用中，哪些能成功推导出 `T`？（多选）

A. `f<>(3.14)` — 空尖括号，T 无法推导
B. `f(42)` — T 推导为 `int`
C. `f()` — 无参数，T 无法推导
D. `f('A')` — T 推导为 `char`
E. `f<int>()` — 显式指定但无参数，编译错误
