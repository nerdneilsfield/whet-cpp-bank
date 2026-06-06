---
qid: cpp-poly-adv-013
type: single
kp: [cpp-polymorphism]
difficulty: hard
answer_key: C
---

以下代码结合协变返回类型与 CRTP，`p->clone()` 返回的**静态类型**是什么？运行时输出是什么？

```cpp
#include <cstdio>

struct Base {
    virtual Base* clone() const {
        puts("Base::clone");
        return new Base(*this);
    }
    virtual ~Base() {}
};

struct Derived : Base {
    Derived* clone() const override {   // 协变返回类型
        puts("Derived::clone");
        return new Derived(*this);
    }
};

int main() {
    Base* p = new Derived();
    auto* q = p->clone();   // q 的静态类型是？输出是？
    printf("%s\n", typeid(*q).name());
    delete q;
    delete p;
}
```

A. `q` 静态类型 `Derived*`，输出 `Derived::clone` 和 `Derived` 的 typeid
B. `q` 静态类型 `Derived*`，因为协变返回类型在多态调用时保留派生类型
C. `q` 静态类型 `Base*`（通过 `Base*` 指针调用，返回类型退化为 `Base*`），输出 `Derived::clone`，typeid 显示 `Derived`
D. 编译错误：协变返回类型与虚函数 override 不能同时使用

---

**解析：**

协变返回类型（Covariant Return Type）的关键规则：
- **虚函数分派**（动态）决定调用哪个 `clone()`：`p` 的动态类型是 `Derived`，所以调用 `Derived::clone()`，输出 `Derived::clone`。
- **返回类型的静态推断**取决于**调用表达式的静态类型**：`p` 是 `Base*`，`p->clone()` 的静态类型是 `Base*`（编译器看到的是 `Base::clone` 的声明），即使运行时实际返回 `Derived*`。
- 因此 `auto* q` 推断为 `Base*`，但 `*q` 的动态类型是 `Derived`，`typeid(*q)` 显示 `Derived`。

若通过 `Derived*` 调用：`Derived* d = new Derived(); auto* r = d->clone();` 则 `r` 静态类型是 `Derived*`——这才是协变返回的好处所在。

## Explanation

正确答案是 C，因为该选项对应 ``q` 静态类型 `Base*`（通过 `Base*` 指针调用，返回类型退化为 `Base*`），输出 `Derived::clone`，typeid 显示 `Derived``，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
