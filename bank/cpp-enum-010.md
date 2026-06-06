---
qid: cpp-enum-010
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: D
---
以下代码是否合法？

```cpp
enum A { X, Y };
enum B { X, Z };   // X 在同一命名空间内重复定义
```

A. 合法，两个 X 属于不同枚举，不冲突
B. 合法，仅发出警告
C. 合法，后者覆盖前者
D. 编译错误：传统 enum 的枚举器直接注入外层命名空间，`X` 重定义

## Explanation

正确答案是 D。枚举题的核心是区分传统 `enum` 与 `enum class` 的作用域、隐式转换和底层类型规则。选项 D 的表述“编译错误：传统 enum 的枚举器直接注入外层命名空间，｀X｀ 重定义”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
