---
qid: cpp-move-018
type: multi
kp: [cpp-move-semantics]
difficulty: easy
answer_key: [B, D]
---

# 代码阅读：哪些是 lvalue？

以下表达式中，哪些是 **lvalue**？（多选）

```cpp
int x = 10;
int y = 20;
std::string s = "hi";
```

A. `x + y`
B. `x`
C. `42`
D. `s`
E. `std::string("temp")`

## Explanation

正确答案是 B、D，具名变量 `x` 和 `s` 都是左值表达式。`x + y` 和字面量 `42` 是临时结果或纯右值，`std::string("temp")` 也是临时对象。判断左值的关键不是出现位置，而是表达式是否表示有身份的对象。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
