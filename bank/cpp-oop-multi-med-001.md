---
qid: cpp-oop-multi-med-001
type: multi
kp: [cpp-inheritance]
difficulty: medium
answer_key: [A, C, D]
---
关于虚函数的语义，**哪些说法是正确的**？（多选）

```cpp
struct Base {
    Base() { foo(); }              // (1)
    virtual ~Base() { foo(); }     // (2)
    virtual void foo() { puts("Base"); }
};
struct Derived : Base {
    void foo() override { puts("Derived"); }
};
Derived d;
```

A. 在 `Base` 的构造函数中调用 `foo()`，调用的是 `Base::foo`，不会派发到 `Derived::foo`（构造期间动态类型尚未变成 `Derived`）
B. 通过对象（非指针/引用）调用虚函数仍走动态派发，例如 `Base b = d; b.foo();` 调用 `Derived::foo`
C. 在 `Base` 的析构函数中调用 `foo()`，调用的也是 `Base::foo`（析构期间动态类型已"退回"基类）
D. 基类析构函数应声明为 `virtual`，否则通过 `Base*` 删除 `Derived*` 时只调用 `Base::~Base`，可能泄漏 `Derived` 部分的资源

---

**解析：**

A 正确：构造期间对象的动态类型尚是 `Base`，虚表指针指向 `Base` 的 vtable，调用解析为 `Base::foo`。这是 Effective C++ 的经典条款。
B 错误：通过对象本身（按值）调用是**静态派发**，`Base b = d` 还会触发对象切片（slicing）；`b.foo()` 调用 `Base::foo`，不会调用 `Derived::foo`。
C 正确：析构顺序与构造相反，进入基类析构时派生部分已销毁，虚表回到基类版本，调用 `Base::foo`。
D 正确：多态删除必须基类析构虚化，否则未定义行为（可能仅调用基类析构）。