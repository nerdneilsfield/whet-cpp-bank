---
qid: cpp-enum-018
type: fill
kp: [cpp-enum]
difficulty: easy
answer_key: "enum class Dir : uint8_t"
---
声明一个名为 `Dir` 的有作用域枚举，底层类型为 `uint8_t`，填写完整的枚举头（不含花括号及枚举器）：

```cpp
___ { North, South, East, West };
```

## Explanation

应填 `enum class Dir : uint8_t`。枚举题的核心是区分传统 `enum` 与 `enum class` 的作用域、隐式转换和底层类型规则。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
