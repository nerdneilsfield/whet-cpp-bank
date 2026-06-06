---
qid: cpp-algo-deep-012
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

对**空范围**调用，下列断言哪项**全部正确**？

```cpp
std::vector<int> v;  // 空
bool a = std::all_of (v.begin(), v.end(), [](int){return false;});
bool b = std::any_of (v.begin(), v.end(), [](int){return true;});
bool c = std::none_of(v.begin(), v.end(), [](int){return true;});
```

A. `a = false, b = true,  c = false`
B. `a = false, b = false, c = true`
C. `a = true,  b = false, c = true`
D. `a = true,  b = true,  c = true`

---

**解析：**

空范围（vacuous truth）：

- `all_of` 空 → **true**（没有元素能反例化）
- `any_of` 空 → **false**（没有元素能满足）
- `none_of` 空 → **true**（没有元素违反）

满足等式 `none_of == !any_of`，且 `all_of && none_of` 在空集上同时为真。设计时需注意：在边界条件下 `all_of` 为真不能等同于"集合非空且全满足"。
