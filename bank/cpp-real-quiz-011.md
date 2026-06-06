---
qid: cpp-real-quiz-011
type: single
kp: [cpp-polymorphism, cpp-special-members]
primary_kp: cpp-polymorphism
difficulty: hard
answer_key: A
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的输出是？

```cpp
#include <iostream>
struct Base {
    Base() { f(); }
    virtual void f() { std::cout << "Base"; }
};
struct Derived : Base {
    void f() override { std::cout << "Derived"; }
};
int main() {
    Derived d;
}
```

A. `Base`
B. `Derived`
C. 未定义行为
D. 编译错误

---

**解析：**

[class.cdtor]/4：在**构造函数运行期间**，对象的动态类型就是**正在构造的那个类本身**（这里是 `Base`），而不是最终派生类型。所以构造 `Derived d` 时先调 `Base()`，在 `Base()` 中虚函数 `f()` 的调用解析为 **`Base::f`**，输出 `Base`。

vptr 的设置是分阶段的：每个构造函数进入时把 vptr 改写为本类的 vtable，构造完成后才轮到派生类构造函数把 vptr 改写为派生类的。析构期间反向。

这就是为什么《Effective C++》第 9 条说"绝不在构造或析构函数中调用虚函数"——你以为是动态分发，其实是静态分发。

**来源：** Effective C++ Item 9；C++17 [class.cdtor]/4

## Explanation

正确答案是 A。
[class.cdtor]/4：在构造函数运行期间，对象的动态类型就是正在构造的那个类本身（这里是 Base），而不是最终派生类型；所以构造 Derived d 时先调 Base()，在 Base() 中虚函数 f() 的调用解析为 Base::f，输出 Base。
vptr 的设置是分阶段的：每个构造函数进入时把 vptr 改写为本类的 vtable，构造完成后才轮到派生类构造函数把 vptr 改写为派生类的；析构期间反向。
所以构造 Derived d 时先调 Base()，在 Base() 中虚函数 f() 的调用解析为 Base::f，输出 Base。
