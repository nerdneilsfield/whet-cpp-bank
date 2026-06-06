---
qid: cpp-cast-r-004
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: B
---

## 题目

下面代码的输出是什么？

```cpp
#include <iostream>

struct Animal {
    virtual ~Animal() = default;
};

struct Dog : Animal {
    void bark() { std::cout << "Woof!" << std::endl; }
};

struct Cat : Animal {};

int main() {
    Animal* a = new Cat();
    Dog* d = dynamic_cast<Dog*>(a);
    if (d == nullptr) {
        std::cout << "cast failed" << std::endl;
    } else {
        d->bark();
    }
    delete a;
    return 0;
}
```

A. 输出 `Woof!`
B. 输出 `cast failed`
C. 编译错误：`Cat` 和 `Dog` 不相关
D. 运行时抛出异常

## 答案

B

## 解析

`dynamic_cast` 在运行时检查对象的实际类型。`a` 指向的对象实际类型是 `Cat`，无法转换为 `Dog*`，因此 `dynamic_cast<Dog*>(a)` 返回 `nullptr`。程序输出 `cast failed`。`dynamic_cast` 对指针类型失败返回 `nullptr`（对引用类型失败则抛出 `std::bad_cast`）。`Animal` 有虚函数（`virtual ~Animal()`），满足多态基类的要求，`dynamic_cast` 才能正常工作。
