---
qid: cpp-move-adv-004
type: single
kp: [cpp-move-semantics]
difficulty: medium
answer_key: C
---

下列代码中，`f(x)` 与 `f(42)` 的调用分别使 T 推导为什么？

```cpp
template<typename T>
void f(T&& val) {
    // ...
}

int x = 5;
f(x);   // (1)
f(42);  // (2)
```

A. (1) T = `int`；(2) T = `int`
B. (1) T = `int&`；(2) T = `int&`
C. (1) T = `int&`；(2) T = `int`
D. (1) T = `int&&`；(2) T = `int&&`

---

**解析：**

转发引用模板参数推导规则：
- 传入**左值**（`x` 是左值，类型 `int`）：T 推导为 `int&`，`T&&` = `int& &&` = `int&`（折叠）。
- 传入**右值**（`42` 是右值，类型 `int`）：T 推导为 `int`，`T&&` = `int&&`。

选 C。这是转发引用最基本的推导规律，需熟记。
