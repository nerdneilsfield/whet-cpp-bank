---
qid: cpp-poly-019
type: fill
kp: [cpp-polymorphism]
difficulty: easy
answer_key: "Base*（或 Base 的指针/引用），协变返回类型"
---

# 填空题：协变返回类型

阅读以下代码：

```cpp
struct Base {
    virtual Base* clone() const;
};
struct Derived : Base {
    Derived* clone() const override;   // 返回类型从 Base* 变为 Derived*
};
```

这里 `Derived::clone()` 的返回类型从 `______` 变为 `Derived*`，这在 C++ 中是合法的，称为 ______。

## Explanation

填空应为 `Base*（或 Base 的指针/引用），协变返回类型`，因为这是题干所问概念或语法在 C++ 中的标准写法。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
