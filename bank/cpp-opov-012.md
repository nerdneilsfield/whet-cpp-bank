---
qid: cpp-opov-012
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: B
---

以下代码输出是什么？

```cpp
struct Counter {
    int v = 0;
    Counter& operator++() { ++v; return *this; }       // 前置
    Counter  operator++(int) { Counter t = *this; ++v; return t; } // 后置
};

Counter c;
Counter d = c++;
// 此时 c.v = ?, d.v = ?
```

A. `c.v = 0, d.v = 0`
B. `c.v = 1, d.v = 0`
C. `c.v = 0, d.v = 1`
D. `c.v = 1, d.v = 1`
