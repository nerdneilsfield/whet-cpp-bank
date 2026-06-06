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

## 解析

正确答案是 C，因为该选项对应 `8`，符合题中代码或概念的 C++ 语义。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
