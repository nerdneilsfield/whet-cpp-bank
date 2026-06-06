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

## 解析

正确答案是 B，因为该选项对应 ``c.v = 1, d.v = 0``，符合题中代码或概念的 C++ 语义。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
