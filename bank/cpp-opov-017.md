---
qid: cpp-opov-017
type: multi
kp: [cpp-operator-overload]
difficulty: easy
answer_key: [B, D]
---

以下代码片段中，哪几行会导致**编译错误**？（多选）

```cpp
struct Num {
    int v;
    Num(int v) : v(v) {}
    Num operator+(const Num& r) const { return Num(v + r.v); }
    Num& operator+=(const Num& r) { v += r.v; return *this; }
};

Num a(1), b(2);
Num c = a + b;           // 行1
a += b;                  // 行2
Num d = a * b;           // 行3  ← ?
int e = sizeof(Num);     // 行4
```

A. 行1
B. 行3
C. 行4
D. 行3（`*` 未重载，无法匹配）
E. 行4（`sizeof` 不可用于用户类型）
