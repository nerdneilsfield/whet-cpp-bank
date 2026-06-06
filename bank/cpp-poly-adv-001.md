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
