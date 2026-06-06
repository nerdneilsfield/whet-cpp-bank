---
qid: cpp-real-quiz-009
type: single
kp: [cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: hard
answer_key: B
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的输出是？

```cpp
#include <iostream>
struct Base { virtual void f() { std::cout << "Base"; } };
struct Derived : Base { void f() override { std::cout << "Derived"; } };
int main() {
    Base* p = new Derived;
    p->f();
    delete p;
}
```

A. `Base`
B. `Derived`
C. 未定义行为
D. 编译错误

---

**解析：**

经典虚函数 dispatch：`Base* p` 指向派生类对象，`p->f()` 通过 vptr/vtable 运行时查找 `Derived::f`，输出 `Derived`。

`delete p` 时基类 `~Base()` 未标记 `virtual` → 这是当前场景（题目故意不写 virtual dtor）。按 [expr.delete]/3，如果基类析构函数不是 virtual 且类型不匹配，**行为未定义**。不过这个 UB 不影响输出，动态类型依然通过 vptr 正确找到 `Derived::f`，但析构中的 UB 可能会给内存管理带来问题。

此处追问 `p->f()` 本身仍保证输出 `Derived`。

选错了的同学往往是没理解虚函数究竟何时走派生类版本——vptr 在构造完成后就一直指向派生类。但注意限考的是 `f()` 本身的表现，析构的 UB 不会诡异地让 `f()` 输出 Base。

**来源：** cppquiz.org Question #53；C++17 [class.virtual]

## Explanation

正确答案是 B。
经典虚函数 dispatch：Base p 指向派生类对象，p->f() 通过 vptr/vtable 运行时查找 Derived::f，输出 Derived；delete p 时基类 ~Base() 未标记 virtual → 这是当前场景（题目故意不写 virtual dtor）。
按 [expr.delete]/3，如果基类析构函数不是 virtual 且类型不匹配，行为未定义；不过这个 UB 不影响输出，动态类型依然通过 vptr 正确找到 Derived::f，但析构中的 UB 可能会给内存管理带来问题。
此处追问 p->f() 本身仍保证输出 Derived。
