---
qid: cpp-algo-multi-deep-002
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: [B, C]
---

关于 `std::sort` 比较器要求，下列哪些是**严格弱序**的必要条件？（多选）

```cpp
auto cmp = [](const T& a, const T& b){ return /* ... */; };
std::sort(v.begin(), v.end(), cmp);
```

A. `cmp(a, b) ⇒ cmp(b, a)`（对称性）
B. `cmp(a, a) == false`（反自反性 / irreflexivity）
C. `cmp(a, b) && cmp(b, c) ⇒ cmp(a, c)`（传递性）
D. 必须返回 `std::strong_ordering`

---

**解析：**

严格弱序要求：
- B ✅ 反自反性
- C ✅ 传递性
- 反对称性（asymmetry）：`cmp(a,b) ⇒ !cmp(b,a)`（A 写反了——A 说的是"对称"，会破坏排序）
- 等价的传递性：`!cmp(a,b) && !cmp(b,a)` 是等价关系且传递

违反任一会导致 `std::sort` 进入 UB（实际表现为崩溃、死循环或越界）。`std::less` 在大多数内置类型上满足，但对 `NaN` 浮点不满足（需自定义处理）。

D 错：比较器只需返回 `bool`；`std::strong_ordering` 是 C++20 三向比较，用于 spaceship。
