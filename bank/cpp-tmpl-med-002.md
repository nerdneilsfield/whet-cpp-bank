---
qid: cpp-tmpl-med-002
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: C
---
下列模板代码哪个写法是正确的？

```cpp
template<typename T>
void f() {
    T::value_type x;            // (1)
    typename T::value_type y;   // (2)
    T::value_type* p;           // (3)
}
```

A. (1) 正确，(2) 多余
B. (3) 是定义一个指针变量 p
C. 必须写 (2)：依赖名 `T::value_type` 须用 `typename` 显式声明为类型
D. 三者都正确

---

**解析：**

模板里的“依赖名”（dependent name，含义随模板参数 `T` 变化的名字）默认被假定为**非类型**（变量、函数等）。要把 `T::value_type` 当作类型使用，必须前缀 `typename` 关键字告诉编译器“它是类型”。(1) 编译失败（编译器把 `T::value_type` 当变量名再后跟 `x` 是语法错误）；(3) 在两阶段查找的第一阶段，会被解析为 `T::value_type * p`（乘法表达式），并非指针声明。C++20 起在“显然只能是类型”的上下文中放宽了 `typename` 的强制要求。

## 解析

正确答案是 C，即 必须写 (2)：依赖名 `T::value_type` 须用 `typename` 显式声明为类型。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
