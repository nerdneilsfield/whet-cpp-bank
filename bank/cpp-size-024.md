---
qid: cpp-size-024
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: D
---

以下代码在大多数平台上的行为是？

```cpp
int x = INT_MAX;
x = x + 1;
```

A. x 变为 INT_MIN（C++ 标准保证）
B. x 变为 0
C. 编译器报错
D. 未定义行为（Undefined Behavior）
