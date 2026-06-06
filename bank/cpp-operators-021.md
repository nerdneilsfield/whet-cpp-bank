---
qid: cpp-operators-021
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: C
---

以下表达式的计算结果是多少？（注意运算符优先级）

```cpp
int result = 2 + 3 * 4;
```

A. 20
B. 24
C. 14
D. 10

## Explanation

正确答案是 C，因为该选项对应 `14`，符合题中代码或概念的 C++ 语义。运算符题的关键是先按 C++ 的优先级、结合性和求值规则拆表达式，再判断每一步的值。常见误区是把按位运算和逻辑运算混淆，或误以为所有二元运算都会短路求值。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
