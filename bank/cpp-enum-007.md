---
qid: cpp-enum-007
type: fill
kp: [cpp-enum]
difficulty: easy
answer_key: "static_cast<int>(Dir::South)"
---
`enum class Dir { North, South, East, West };`，要将 `Dir::South` 转为整数并赋值给 `int x`，正确的右侧表达式是（填完整转换写法）：

```cpp
int x = ___;
```

## Explanation

应填 `static_cast<int>(Dir::South)`。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
