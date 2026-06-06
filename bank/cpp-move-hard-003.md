---
qid: cpp-move-hard-003
type: single
kp: [cpp-move-semantics]
difficulty: hard
answer_key: D
---

关于引用折叠规则，以下哪个推导正确？

```cpp
template<typename T>
void f(T&& param);

int x = 0;
int& rx = x;
const int& crx = x;

f(x);     // T = ?
f(rx);    // T = ?
f(crx);   // T = ?
f(42);    // T = ?
```

A. `int&`, `int&`, `const int&`, `int`
B. `int&&`, `int&&`, `const int&&`, `int&&`
C. `int`, `int&`, `const int&`, `int&&`
D. `int&`, `int&`, `const int&`, `int`

## Explanation

这是 Scott Meyers 经典 T&& 推导（也叫 forwarding reference / universal reference）。规则为：

- 实参为左值表达式 → `T` 推导为 `X&`，`T&&` ⇒ `X& &&` → 折叠为 `X&`
- 实参为右值表达式 → `T` 推导为 `X`，`T&&` ⇒ `X&&`

推导：
- `f(x)`：`x` 是左值 → `T = int&`，参数类型 `int& && → int&`
- `f(rx)`：`rx` 是 `int&` 但出现在表达式中是左值引用表达式，仍是左值 → `T = int&`，参数类型 `int&`
- `f(crx)`：`crx` 是左值表达式 → `T = const int&`，参数类型 `const int&`
- `f(42)`：`42` 是纯右值 → `T = int`，参数类型 `int&&`

折叠规则：`T& & = T&`、`T& && = T&`、`T&& & = T&`、`T&& && = T&&`。
