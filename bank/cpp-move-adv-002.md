---
qid: cpp-move-adv-002
type: fill
kp: [cpp-move-semantics]
difficulty: medium
answer_key: T 推导为 int&，T&& 折叠为 int&
---

给定：

```cpp
template<typename T>
void f(T&& x) { /* ... */ }

int a = 10;
f(a);   // 调用 (1)
```

调用 (1) 中，`T` 被推导为 ______，形参 `x` 的实际类型为 ______。

---

**解析：**

传入 `a` 是一个**左值**（lvalue）。转发引用的推导规则：
- 传入左值 `T` 类型（设为 `X`）：T 推导为 `X&`（即 `int&`）。
- 然后 `T&&` = `int& &&`，按引用折叠规则变为 `int&`（左值引用）。

因此：
- T = `int&`
- x 的类型 = `int&`（绑定到左值 `a`）

这也是转发引用能"透明传递"左值的基础。
