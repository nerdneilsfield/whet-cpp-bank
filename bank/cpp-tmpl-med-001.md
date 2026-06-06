---
qid: cpp-tmpl-med-001
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: B
---
下列代码片段使用 SFINAE，下列说法正确的是？

```cpp
#include <type_traits>
template<typename T,
         typename = std::enable_if_t<std::is_integral_v<T>>>
T add(T a, T b) { return a + b; }
```

A. 当传入 `double` 时编译器会报硬错误（hard error）
B. 当传入 `double` 时，`enable_if_t` 替换失败，模板从重载集合中移除（“替换失败不是错误”）
C. `enable_if` 必须放在返回类型位置才能正常工作
D. 该写法只在 C++20 后才有效

---

**解析：**

SFINAE（Substitution Failure Is Not An Error）是 C++ 模板的核心规则：模板实参替换时若得到非法类型/表达式，不视为编译错误，只把该候选从重载集合中悄悄移除。`std::enable_if_t<...>` 在条件为假时不定义嵌套 `type`，访问 `::type` 失败 → 模板被丢弃。`enable_if` 可放在三种位置（默认模板形参、返回类型、形参类型），任何一种都能触发 SFINAE。C++17 后通常被 `if constexpr` 或 C++20 的 concepts 替代，更易读。
