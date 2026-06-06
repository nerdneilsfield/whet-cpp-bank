---
qid: cpp-enum-short-001
type: short
kp: [cpp-enum]
difficulty: medium
rubric:
  - 指出传统 enum 会把枚举值注入到外层作用域，污染命名空间
  - 指出传统 enum 隐式转换为 int，类型安全弱
  - 解释 enum class（强类型枚举）的特点：作用域限定、不隐式转 int、可显式指定底层类型
  - 给出示例 enum class Color : uint8_t { Red, Green };
---
请对比传统 `enum` 与 C++11 引入的 `enum class`（强类型枚举）的差异。

---

**参考答案：**

传统 `enum` 把枚举值注入到包含其定义的作用域中，容易出现命名冲突，且枚举值会隐式转换为 `int`，参与算术运算或被传给整型形参，类型安全弱。`enum class`（强类型枚举）解决两个问题：枚举值的名字被限定在 enum 的作用域内，使用必须写 `Color::Red`；并且不会隐式转换为整型，需要显式 `static_cast<int>(c)`。另外 `enum class` 可显式指定底层类型，如 `enum class Color : uint8_t { Red, Green };`，有利于控制存储大小和与 ABI 兼容。

## Explanation

`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。 本题短答应围绕核心概念展开：传统 ｀enum｀ 把枚举值注入到包含其定义的作用域中，容易出现命名冲突，且枚举值会隐式转换为 ｀int｀，参与算术运算或被传给整型形参，类型安全弱。｀enum class｀（强类型枚举）解决两个问题：枚举值的名字被限定在 enum 的作用域内，使用必须写 ｀Color::Red｀；并且不会隐式转换为整型，需要显式 ｀static_cast<int>(c)｀。另外 ｀enum class｀ 可显式指定底层类型，如 ｀enum class Color : uint8_t { Red, Green };｀，有利于控制存 评分重点包括：指出传统 enum 会把枚举值注入到外层作用域，污染命名空间；指出传统 enum 隐式转换为 int，类型安全弱；解释 enum class（强类型枚举）的特点：作用域限定、不隐式转 int、可显式指定底层类型。常见误区是只给出结论、不说明机制，或忽略异常路径、同步边界、生命周期等限制条件。
