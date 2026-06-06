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

## Explanation

正确答案是 B, D。B 项 `行3` 符合规则；D 项 `行3（`*` 未重载，无法匹配）` 符合规则；A 项 `行1` 不满足该规则；C 项 `行4` 不满足该规则。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 多选题常见误区是只看关键字相似就勾选，而没有逐项检查它是否真的满足题干条件。
