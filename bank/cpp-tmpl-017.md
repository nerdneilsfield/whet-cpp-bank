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

## Explanation

正确选项是 B（`f(42)` — T 推导为 `int`）、D（`f('A')` — T 推导为 `char`），它们符合本题涉及的 C++ 规则。A（`f<>(3.14)` — 空尖括号，T 无法推导）、C（`f()` — 无参数，T 无法推导） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
