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
