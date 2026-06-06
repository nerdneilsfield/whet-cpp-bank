---
qid: cpp-types-006
type: single
kp: [cpp-types]
difficulty: easy
answer_key: C
---
下列代码能否通过编译？

```cpp
const int n = 10;
n = 20;
```

A. 能，`const` 只是建议，不强制
B. 能，第二行会被编译器忽略
C. 不能，`const` 变量不可被赋值修改
D. 能，但运行时会报错

## Explanation

正确答案是 C，即 不能，`const` 变量不可被赋值修改。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。类型题要关注值类别、cv 限定、隐式转换和推导规则；常见错误是忽略顶层/底层 const 或数组/函数退化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
