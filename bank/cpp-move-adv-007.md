---
qid: cpp-move-adv-007
type: fill
kp: [cpp-move-semantics]
difficulty: medium
answer_key: int&
---

在模板推导中，若 `T = int&`，则 `T&&` 经引用折叠后的类型为 ______。

```cpp
// 辅助理解：
// T = int&
// T&& = (int&) && = int& && = ?
```

---

**解析：**

代入 T = `int&`：
```
T&&  = (int&)&&  = int& &&
```

引用折叠：有左值引用 (`&`) 参与 → 结果为左值引用。

`int& && → int&`

因此答案是 `int&`（左值引用）。

这解释了为什么转发引用传入左值后，形参类型是左值引用——左值参数使 T 推导为 `int&`，再经折叠维持左值引用语义。
