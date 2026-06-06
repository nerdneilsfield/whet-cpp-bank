---
qid: cpp-tmpl-multi-hard-005
type: multi
kp: [cpp-templates]
difficulty: hard
answer_key: [A, B, D]
---
关于模板特化（specialization）的规则，以下说法正确的是哪些？

```cpp
template<typename T, typename U> struct S { };
template<typename T> struct S<T, int> { };       // (1)
template<> struct S<int, int> { };               // (2)

template<typename T> void f(T) { }
template<typename T> void f(T*) { }              // (3)
// template<typename T> void f<T*>(T*) {}       // (4) 假设要这么写
```

A. (1) 是部分特化（partial specialization），(2) 是全特化（full/explicit specialization），二者都是类模板允许的。
B. 函数模板不允许部分特化；(3) 不是部分特化而是**函数模板重载**，由重载解析选择。
C. 函数模板可以全特化也可以部分特化，与类模板规则完全一致。
D. 类模板的部分特化数量任意，重载解析时编译器会选择"最特化"（most specialized）的版本，若无唯一最特化则报歧义。

---

**解析：**

A 正确：类模板既允许全特化（所有参数都确定）也允许部分特化（部分参数固定或带约束），这是标准明确允许的两种形式。
B 正确：(3) 是函数模板重载——`f(T*)` 与 `f(T)` 是两个独立的主模板，重载解析时根据实参类型选择匹配最好的那个，并非部分特化。
C 错误：函数模板**只允许全特化**，不允许部分特化（这是 C++ 历史上有名的"缺陷"，导致大量函数需要用重载或类模板间接绕过），与类模板规则不一致。
D 正确：部分特化数量不限，编译器按"偏序"关系挑选最特化版本，若多个特化互相不可比则产生歧义编译错误。
