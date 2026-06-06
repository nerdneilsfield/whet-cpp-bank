---
qid: cpp-poly-adv-001
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: B
---

阅读以下 CRTP 代码，`obj.draw()` 会输出什么？

```cpp
#include <iostream>

template <typename Derived>
struct Base {
    void draw() {
        static_cast<Derived*>(this)->draw_impl();
    }
};

struct Circle : Base<Circle> {
    void draw_impl() { std::cout << "Circle::draw_impl\n"; }
};

struct Square : Base<Square> {
    void draw_impl() { std::cout << "Square::draw_impl\n"; }
};

int main() {
    Circle obj;
    obj.draw();
}
```

A. `Base::draw_impl`（基类默认实现）
B. `Circle::draw_impl`
C. 编译错误：`draw_impl` 不在 `Base` 中
D. 运行时崩溃：`static_cast` 转换不安全

---

**解析：**

CRTP（Curiously Recurring Template Pattern）通过 `static_cast<Derived*>(this)` 将基类指针向下转换为派生类指针，然后调用 `draw_impl()`。

- 实例化时 `Derived = Circle`，所以 `static_cast<Circle*>(this)->draw_impl()` 直接静态绑定到 `Circle::draw_impl`。
- 整个过程在**编译期**完成，无虚表查找，无运行时开销。
- 因为 `Circle` 继承自 `Base<Circle>`，`this` 指针指向的对象确实是 `Circle`，`static_cast` 安全。

## Explanation

正确答案是 B，因为该选项对应 ``Circle::draw_impl``，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
