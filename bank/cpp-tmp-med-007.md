---
qid: cpp-tmp-med-007
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: B
---

以下代码的输出是什么？

```cpp
#include <iostream>

template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->impl();
    }
};

class Dog : public Base<Dog> {
public:
    void impl() { std::cout << "Dog::impl" << std::endl; }
};

class Cat : public Base<Cat> {
public:
    void impl() { std::cout << "Cat::impl" << std::endl; }
};

int main() {
    Dog d;
    Cat c;
    d.interface();
    c.interface();
}
```

A. `Base::impl` / `Base::impl`
B. `Dog::impl` / `Cat::impl`
C. 编译错误：Base 中没有定义 `impl()`
D. `Dog::impl` / `Dog::impl`

---

**解析：**

CRTP 实现静态多态：`Base<Derived>::interface()` 通过 `static_cast<Derived*>(this)->impl()` 将调用分派到派生类的 `impl()`。  
编译期，`Derived` 已经是具体类型（`Dog` 或 `Cat`），`static_cast` 合法且零开销。  
`d.interface()` → `Dog::impl`，`c.interface()` → `Cat::impl`，输出 B。
