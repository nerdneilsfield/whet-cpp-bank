---
qid: cpp-poly-r-001
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: "B"
---

## 题目

阅读以下代码，运行后输出是什么？

```cpp
#include <iostream>

struct Animal {
    virtual void speak() { std::cout << "Animal\n"; }
};

struct Dog : Animal {
    void speak() override { std::cout << "Dog\n"; }
};

int main() {
    Animal* p = new Dog();
    p->speak();
    delete p;
}
```

A. `Animal`
B. `Dog`
C. 编译错误
D. 未定义行为

## 解析

`speak()` 是虚函数，`p` 的静态类型是 `Animal*`，但运行时实际对象是 `Dog`。虚函数通过 vtable 实现动态分派，调用的是 `Dog::speak()`，输出 `Dog`。
