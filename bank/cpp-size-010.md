---
qid: cpp-size-010
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: B
---

以下关于结构体 `sizeof` 的描述，哪项正确？

```cpp
struct S { char a; int b; };
```

A. `sizeof(S)` 一定等于 `sizeof(char) + sizeof(int)` = 5
B. `sizeof(S)` 可能大于 5，因为编译器可能在成员之间插入对齐填充
C. `sizeof(S)` 一定等于 8
D. `sizeof(S)` 的结果无法在编译期确定
