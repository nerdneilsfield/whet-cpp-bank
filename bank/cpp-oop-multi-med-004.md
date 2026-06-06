---
qid: cpp-oop-multi-med-004
type: multi
kp: [cpp-inheritance]
difficulty: medium
answer_key: [A, B, C]
---
关于对象切片（object slicing）的场景和后果，**哪些说法是正确的**？（多选）

```cpp
struct Base { virtual void f() { puts("B"); } int b = 1; };
struct Derived : Base {
    void f() override { puts("D"); }
    int d = 2;
};

Derived d;
Base b1 = d;        // (1) 切片
b1.f();

Base& r = d;        // (2) 无切片
r.f();
Base* p = &d;       // (3) 无切片

Base b2;
b2 = d;             // (4) 切片
```

A. (1) 发生切片：只拷贝了 `b` 部分，`f()` 调用 `Base::f()` 而不是 `Derived::f()`
B. (2)(3) 未发生切片，`r.f()` 和 `p->f()` 通过虚表正确调用 `Derived::f()`
C. (4) 通过拷贝赋值发生切片，只赋值了 `Base` 部分的 `b`，`Derived` 独有的 `d` 被丢弃
D. 切片只会发生在继承体系中，且切片后的对象**可以**通过 `dynamic_cast` 还原回派生类类型

---

**解析：**

A 正确：按值构造 `Base` 时只复制基类子对象，派生部分数据丢失；虚表指针被设为 `Base` 的 vtable，`f` 调用 `Base` 版本。
B 正确：引用和指针不切割，动态类型仍是 `Derived`，虚函数正常工作。
C 正确：拷贝赋值同上，`d` 的 `d` 成员被丢弃（只赋值 `b` 部分）。
D 错误：切片后对象的动态类型是 `Base`，vptr 指向 `Base` 的 vtable，`dynamic_cast<Derived&>` 会抛 `std::bad_cast`，`dynamic_cast<Derived*>` 返回 `nullptr`。**切片是不可逆的。**