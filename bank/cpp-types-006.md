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
