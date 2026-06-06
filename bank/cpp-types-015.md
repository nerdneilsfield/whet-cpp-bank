---
qid: cpp-types-015
type: single
kp: [cpp-types]
difficulty: easy
answer_key: B
---
下列代码中，`auto` 推导出的 `y` 类型是什么？

```cpp
float f = 1.5f;
auto y = f;
```

A. `double`
B. `float`
C. `int`
D. `long double`

## Explanation

正确答案是 B，即 `float`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。类型题要关注值类别、cv 限定、隐式转换和推导规则；常见错误是忽略顶层/底层 const 或数组/函数退化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
