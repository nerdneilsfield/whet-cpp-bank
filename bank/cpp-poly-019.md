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
