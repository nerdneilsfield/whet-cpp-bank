---
qid: cpp-tmp-med-015
type: fill
kp: [cpp-templates]
difficulty: medium
answer_key: "int"
---

`std::conditional` 的作用类似于编译期三目运算符。请填写以下表达式的结果类型：

```cpp
#include <type_traits>

// 表达式 1
std::conditional<true, int, double>::type   // 结果类型：____

// 表达式 2
std::conditional<false, int, double>::type  // 结果类型：____

// 表达式 3（C++14 别名）
std::conditional_t<(sizeof(int) < sizeof(long)), int, long>  // 结果类型：____（假设 sizeof(int)=4, sizeof(long)=8）
```

---

**解析：**

- 表达式 1：条件为 `true`，选第一个类型 → **`int`**。
- 表达式 2：条件为 `false`，选第二个类型 → **`double`**。
- 表达式 3：`sizeof(int)=4 < sizeof(long)=8` 为 true，选 `int` → **`int`**（在 LP64 平台）。

`std::conditional<B, T, F>::type`：B 为 true 时等于 T，false 时等于 F。`conditional_t` 是 C++14 引入的别名模板，省去 `::type`。
