---
qid: cpp-move-adv-003
type: fill
kp: [cpp-move-semantics]
difficulty: medium
answer_key: T 推导为 int，T&& 为 int&&
---

给定：

```cpp
template<typename T>
void f(T&& x) { /* ... */ }

f(42);   // 调用 (2)
```

调用 (2) 中，`T` 被推导为 ______，形参 `x` 的实际类型为 ______。

---

**解析：**

传入 `42` 是一个**右值**（rvalue）。转发引用的推导规则：
- 传入右值（类型 `X`）：T 推导为 `X`（不加引用，即 `int`）。
- `T&&` = `int&&`，保持右值引用。

因此：
- T = `int`
- x 的类型 = `int&&`

与题目 002 对比：传左值时 T 多一个 `&`，传右值时 T 是裸类型。这是区分两种情况的核心规律。
