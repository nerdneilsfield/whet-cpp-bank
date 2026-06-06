---
qid: cpp-tmp-med-019
type: fill
kp: [cpp-templates]
difficulty: medium
answer_key: "42"
---

`std::integral_constant` 是类型携带值的基础工具。填写下列各表达式的结果：

```cpp
#include <type_traits>

using T1 = std::integral_constant<int, 42>;
using T2 = std::integral_constant<bool, true>;
using T3 = std::true_type;   // = integral_constant<bool, true>

// 表达式结果：
T1::value          // = ____
T2::value          // = ____
T3::value          // = ____
T1{}()             // = ____（调用 operator()）
std::is_same_v<T2, T3>  // = ____
```

---

**解析：**

- `T1::value` = **42**（`integral_constant<int,42>` 的 `value` 静态成员）
- `T2::value` = **true**
- `T3::value` = **true**（`true_type` 是 `integral_constant<bool, true>` 的别名）
- `T1{}()` = **42**（`integral_constant` 重载了 `operator()`，返回 `value`）
- `std::is_same_v<T2, T3>` = **true**（`std::true_type` 就是 `integral_constant<bool, true>`）

`integral_constant` 是 type traits 的底层积木：`is_integral<int>` 继承自 `integral_constant<bool, true>`，因此 `is_integral<int>::value` = `true`。
