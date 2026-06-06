---
qid: cpp-move-adv-008
type: fill
kp: [cpp-move-semantics]
difficulty: medium
answer_key: int&
---

在模板或 typedef 中，若 `T = int&&`，则 `T&`（即 `(int&&) &`）经引用折叠后的类型为 ______。

```cpp
// 辅助理解：
// T = int&&
// T& = (int&&) & = int&& & = ?
```

---

**解析：**

代入 T = `int&&`：
```
T&  = (int&&)&  = int&& &
```

引用折叠：有左值引用 (`&`) 参与 → 结果为左值引用。

`int&& & → int&`

因此答案是 `int&`（左值引用）。

关键记忆点：**右值引用加上任何左值引用都会"退化"为左值引用**。只有 `&&` + `&&` 才能保持右值引用。
