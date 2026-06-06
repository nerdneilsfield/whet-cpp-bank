---
qid: cpp-cf-010
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: B
---

以下 `while` 循环执行了几次循环体？

```cpp
int i = 10;
while (i > 0) {
    i -= 3;
}
```

A. 3
B. 4
C. 5
D. 无限次

## 解析

正确答案为 B，因为“4”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
