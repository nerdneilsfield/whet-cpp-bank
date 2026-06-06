---
qid: cpp-opov-013
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: A
---

以下代码中，`++c` 调用的是哪个版本的 `operator++`，`c.v` 变为多少？

```cpp
struct Counter {
    int v = 0;
    Counter& operator++() { ++v; return *this; }
    Counter  operator++(int) { Counter t = *this; ++v; return t; }
};

Counter c;
Counter& r = ++c;
```

A. 调用前置版本；`c.v = 1`，`r` 与 `c` 是同一对象
B. 调用后置版本；`c.v = 1`，`r` 是临时副本
C. 调用前置版本；`c.v = 0`，`r` 是临时副本
D. 编译错误，前置 `++` 不返回引用

## 解析

正确答案是 A，因为该选项对应 `调用前置版本；`c.v = 1`，`r` 与 `c` 是同一对象`，符合题中代码或概念的 C++ 语义。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 B 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
