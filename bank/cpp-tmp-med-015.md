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

## Explanation

填入 `int`，因为题目要求的是该规则下的精确表达或标准名称。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
