---
qid: cpp-opov-med-004
type: single
kp: [cpp-operator-overload]
difficulty: medium
answer_key: B
---

C++ 标准对 `operator=`、`operator[]`、`operator()`、`operator->` 这四个运算符的重载位置有特殊限制。下列描述正确的是？

A. 这四个都既能作为成员函数也能作为非成员函数重载
B. 这四个**必须**作为非 static 成员函数重载，不能写成非成员
C. 只有 `operator=` 必须作为成员，其余可以是非成员
D. 只有 `operator()` 和 `operator->` 必须作为成员，`operator=` 和 `operator[]` 可以是非成员

---

**解析：**

[over.oper] 明确规定：`operator=`、`operator[]`、`operator()`、`operator->` 这四个运算符**必须**作为非 static 成员函数重载，不允许声明为非成员（包括 friend 非成员）。

理由各不相同但都关乎语义：
- `operator=`：每个类都隐式声明一个赋值运算符，如果允许非成员，会与隐式成员产生歧义；且赋值天然属于“对自身的操作”。
- `operator[]`：必须知道左操作数的完整类型（包括 cv 重载），成员函数能自动获得 `this` 的 cv 限定，便于区分 `const`/非 `const` 版本。
- `operator()`：函数调用语法 `obj(args)` 强烈暗示这是对象自身的行为。
- `operator->`：返回值还会被链式应用 `->`，需要稳定的成员语义。

注意 `operator++`、`operator+`、`operator<<` 等都没有这条限制，可以是成员也可以是非成员；非成员形式对支持隐式转换的对称运算更友好。

## 解析

正确答案是 B，因为该选项对应 `这四个**必须**作为非 static 成员函数重载，不能写成非成员`，符合题中代码或概念的 C++ 语义。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
