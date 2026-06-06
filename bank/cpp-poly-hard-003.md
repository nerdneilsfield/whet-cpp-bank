---
qid: cpp-poly-hard-003
type: single
kp: [cpp-polymorphism]
difficulty: hard
answer_key: C
---

下列代码是否合法？

```cpp
struct Base { virtual Base* clone() const { return new Base(*this); } };
struct Derived : Base {
    Derived* clone() const override { return new Derived(*this); }
};
```

A. 非法：`override` 要求返回类型必须完全一致
B. 非法：`Derived*` 不是 `Base*` 的派生类型
C. 合法：这是协变返回类型（covariant return），返回类型可放宽为返回基类类型派生指针/引用
D. 合法但 `override` 关键字必须去掉

## Explanation

C++ 允许虚函数的**协变返回类型（covariant return types）**：派生类重写的返回类型可以是基类返回类型的派生**指针或引用**（不能用于值类型或智能指针），且派生关系在重写时点必须可见、可访问、可隐式转换。这是 clone 模式的语法基础。编译器自动在调用现场插入指针调整。`override` 仍然有效——它要求确实覆盖了基类的虚函数，而协变返回是允许的重写形式之一。注意：智能指针的返回类型不享受协变规则（因为 `unique_ptr<Derived>` 不是 `unique_ptr<Base>` 的子类型）；这就是为何手写 clone 通常返回裸指针并由调用方包装。
