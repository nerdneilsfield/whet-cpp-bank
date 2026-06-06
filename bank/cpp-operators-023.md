---
qid: cpp-operators-023
type: fill
kp: [cpp-operators]
difficulty: easy
answer_key: "97"
---

在 C++ 中，`char` 类型在算术运算中会发生整数提升（integral promotion）。以下表达式的结果类型是 `int`，其值是多少？

```cpp
char c = 'a';   // 'a' 的 ASCII 码为 97
int result = c + 0;
```

答：___

## Explanation

填空应为 `97`，因为这是题干所问概念或语法在 C++ 中的标准写法。运算符题的关键是先按 C++ 的优先级、结合性和求值规则拆表达式，再判断每一步的值。常见误区是把按位运算和逻辑运算混淆，或误以为所有二元运算都会短路求值。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
