---
qid: cpp-poly-adv-009
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: A
---

下列代码中，`Base* p` 在执行完 `p = new Derived()` 后，`p` 所指对象内的 **vptr 值**与直接构造 `Derived d` 时的 vptr 值相比，结论是？

```cpp
#include <cstdio>

struct Base {
    virtual void f() { puts("Base::f"); }
    virtual ~Base() {}
};

struct Derived : Base {
    void f() override { puts("Derived::f"); }
};

int main() {
    Base* p = new Derived();   // (1)
    Derived d;                  // (2)

    // (1) 中 p 所指对象的 vptr 与 (2) 中 d 的 vptr 是否相同？
    p->f();
    d.f();
    delete p;
}
```

A. 相同：两者的 vptr 均指向 `Derived` 的 vtable
B. 不同：`(1)` 中 vptr 指向 `Base` 的 vtable，因为声明类型是 `Base*`
C. 不同：堆对象与栈对象的 vtable 地址不同
D. 不确定：取决于编译器优化级别

---

**解析：**

vptr 在**构造函数**执行期间由编译器注入，取决于对象的**动态类型**（实际构造的类），与指针的静态类型（`Base*`）无关。

- `new Derived()` 调用 `Derived` 的构造函数，vptr 被设为 `Derived` 的 vtable 地址。
- `Derived d` 同样调用 `Derived` 构造函数，vptr 设为相同的 `Derived` vtable 地址。
- vtable 是**类级别**的静态数据，不区分堆/栈，所有 `Derived` 实例共享同一份 vtable。

因此两者 vptr 值**相同**，`p->f()` 和 `d.f()` 均输出 `Derived::f`。
