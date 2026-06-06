---
qid: cpp-smf-018
type: multi
kp: [cpp-special-members]
difficulty: easy
answer_key: [B, D]
---

以下哪些代码行调用的是**拷贝赋值运算符**？（多选）

```cpp
struct T { int v; };
T a{1}, b{2}, c{3};

// (A)
T x = a;

// (B)
b = a;

// (C)
T y(a);

// (D)
c = T{5};
```

A. (A)
B. (B)
C. (C)
D. (D)
