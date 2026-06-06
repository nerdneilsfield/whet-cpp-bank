---
qid: cpp-ub-019
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: D
---

# 无符号整数溢出 vs 有符号整数溢出

```cpp
unsigned int u = 0;
u = u - 1;        // 行 A

int s = INT_MIN;
s = s - 1;        // 行 B
```

关于两行的行为，正确的说法是：

A. 两行都是未定义行为
B. 行 A 是未定义行为，行 B 是合法回绕
C. 两行都是合法的取模回绕
D. 行 A 合法（`unsigned` 溢出结果为 `UINT_MAX`，标准明确规定回绕），行 B 是未定义行为
