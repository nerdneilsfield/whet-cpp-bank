---
qid: cpp-x-poly-inh-002
type: single
kp: [cpp-polymorphism, cpp-inheritance]
primary_kp: cpp-polymorphism
difficulty: medium
answer_key: B
---

下列代码使用 **协变返回类型（covariant return type）**，哪一行编译失败？

```cpp
struct Base {
    virtual Base* clone() const { return new Base(*this); }
};

struct Derived : Base {
    Derived* clone() const override { return new Derived(*this); }  // (1)
};

struct Other { };

struct Mixed : Base {
    Other* clone() const override { return new Other(); }            // (2)
};

struct GrandChild : Derived {
    GrandChild* clone() const override {                              // (3)
        return new GrandChild(*this);
    }
};
```

A. 只有 (1)
B. 只有 (2)
C. (2) 和 (3)
D. (1)(2)(3) 都失败

---

## Explanation

**协变返回类型** 规则（[class.virtual]/8）：派生类重写虚函数时，**返回类型可以是基类版本的派生类**——前提是：

1. 返回类型必须是 **指针或引用**（不能是值类型）。
2. 派生类版本的返回类型 `D*` 中，`D` 必须 **公开继承自** 基类版本返回类型 `B*` 中的 `B`。
3. cv 限定符不变严（不能放宽）。

逐项分析：

- **(1) `Derived* clone() const override`**：`Derived` 公开继承自 `Base`，`Derived*` 协变于 `Base*`。**合法**。
- **(2) `Other* clone() const override`**：`Other` 与 `Base` 没有继承关系，`Other*` 不能协变于 `Base*`。**编译失败**——"invalid covariant return type"。
- **(3) `GrandChild* clone() const override`**：父类是 `Derived`，其 `clone` 返回 `Derived*`。`GrandChild` 公开继承自 `Derived`，`GrandChild*` 协变于 `Derived*`。**合法**。

协变返回类型的常见用途是 **克隆模式（virtual constructor）**：

```cpp
auto* d = static_cast<Derived*>(some_base->clone());
// 用协变后：
Derived* d = some_derived->clone();   // 编译器直接给出 Derived*，无需 cast
```

注意：`std::unique_ptr<Derived>` **不能** 直接协变 `std::unique_ptr<Base>`，因为它们是不同的模板实例化，不存在继承关系。如果想用 unique_ptr 实现 clone，可以让虚函数返回 `Base*` 然后由调用方包装，或用 CRTP 模板技巧。
