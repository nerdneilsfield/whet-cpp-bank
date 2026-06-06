---
qid: cpp-real-ali-007
type: single
kp: [cpp-polymorphism, cpp-inheritance]
primary_kp: cpp-polymorphism
difficulty: hard
answer_key: D
tags: [interview-real, alibaba]
---
```cpp
class Base {
public:
    virtual void show() { std::cout << "Base\n"; }
    void display() { std::cout << "Base display\n"; }  // 非虚
};

class Derived : public Base {
public:
    void show() override { std::cout << "Derived\n"; }
    void display() { std::cout << "Derived display\n"; }  // 隐藏
};

int main() {
    Base* b = new Derived();
    b->show();
    b->display();
    
    Derived d;
    Base& ref = d;
    ref.show();
    ref.display();
    return 0;
}
```
程序输出什么？

A. Derived\nBase display\nDerived\nBase display
B. Base\nBase display\nDerived\nBase display
C. Derived\nDerived display\nDerived\nDerived display
D. Derived\nBase display\nDerived\nBase display

---

**解析：**

选 D。这道题考察的是**重写（override）vs 隐藏（hide）** 的本质区别。

基类指针/引用调用成员函数时：
- **虚函数（virtual）** → 动态绑定（运行时查 vptr → vtable → 调用 Derived::show）
- **非虚函数** → 静态绑定（编译器根据静态类型决定调用哪个版本）

所以：
- `b->show()` 虚函数 → 动态绑定 → Derived::show → "Derived"
- `b->display()` 非虚 → 静态绑定（Base*） → Base::display → "Base display"
- `ref.show()` 虚函数 → 动态绑定 → Derived::show → "Derived"
- `ref.display()` 非虚 → 静态绑定（Base&） → Base::display → "Base display"

**三种区别：**

| 特性 | 重写 (override) | 隐藏 (hide) | 重载 (overload) |
|------|-----------------|-------------|-----------------|
| 范围 | 基类派生类 | 基类派生类 | 同一作用域 |
| 函数名 | 相同 | 相同 | 相同 |
| 参数 | 相同 | 可不同 | 必须不同 |
| virtual 关键字 | 必须 | 不需要 | 不需要 |
| 绑定方式 | 动态绑定 | 静态绑定 | 静态绑定 |

C++ 中加了 `override` 关键字后，如果签名不匹配编译器会报错，这是推荐做法。

**来源：** 阿里 C++ 面试（参考：huihut/interview、cs-offer 项目）