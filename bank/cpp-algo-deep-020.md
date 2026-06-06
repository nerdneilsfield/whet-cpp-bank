---
qid: cpp-algo-deep-020
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: C
---

下列比较器违反严格弱序（strict weak ordering），用于 `std::sort` 是 UB。哪项是**问题所在**？

```cpp
auto cmp = [](int a, int b){ return a <= b; };
std::sort(v.begin(), v.end(), cmp);
```

A. 比较器不能用 lambda
B. 必须传 `std::less<int>{}` 才合法
C. `<=` 违反**反自反性**：`cmp(x,x)` 必须为 `false`，但 `<=` 返回 `true`
D. `<=` 对浮点数不安全

---

**解析：**

严格弱序（strict weak ordering）要求比较器 `cmp` 满足：

1. **反自反性**：`cmp(x, x) == false`
2. **反对称性**：`cmp(a,b) && cmp(b,a)` 不能同时为真
3. **传递性**：`cmp(a,b) && cmp(b,c) ⇒ cmp(a,c)`
4. **不可比的传递性**：`!cmp(a,b) && !cmp(b,a)` 是等价关系

`<=` 在 `x == x` 时返回 `true`，违反 (1)，导致 `std::sort` 内部假设失败，常表现为越界读、死循环、崩溃——**未定义行为**。正确写法用 `<`（`std::less` 默认就是 `<`）。

注意浮点 `NaN`：`<` 也无法构成严格弱序（NaN 与任何值都不可比），需在比较器中先处理 NaN。
