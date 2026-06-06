---
qid: cpp-cf-003
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: A
---

关于"悬空 else"（dangling else），下列说法正确的是？

```cpp
int a = 1, b = 2;
if (a > 0)
    if (b > 3)
        std::cout << "inner";
else
    std::cout << "outer";
```

A. `else` 与最近的 `if`（即 `if (b > 3)`）配对，程序输出 "outer"
B. `else` 与外层 `if`（即 `if (a > 0)`）配对，程序输出 "outer"
C. 编译错误，必须加大括号
D. 程序无任何输出

## Explanation

正确答案为 A，因为“`else` 与最近的 `if`（即 `if (b > 3)`）配对，程序输出 "outer"”符合题干所问的 C++ 规则或代码执行结果。B、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
