---
qid: cpp-opov-011
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: C
---

阅读以下代码，`c` 的值是多少？

```cpp
struct Vec {
    int x;
    Vec(int x) : x(x) {}
    Vec operator+(const Vec& rhs) const { return Vec(x + rhs.x); }
};

Vec a(3), b(5);
Vec c = a + b;
// c.x = ?
```

A. 3
B. 5
C. 8
D. 编译错误
