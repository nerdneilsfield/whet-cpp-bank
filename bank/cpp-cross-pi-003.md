---
qid: cpp-cross-pi-003
type: single
kp: [cpp-polymorphism, cpp-inheritance]
difficulty: easy
answer_key: C
---

以下代码的输出是什么？

```cpp
#include <iostream>

struct Animal {
protected:
    int legs = 4;
public:
    virtual std::string describe() {
        return "Animal legs=" + std::to_string(legs);
    }
};

struct Snake : Animal {
    Snake() { legs = 0; }
    std::string describe() override {
        return "Snake legs=" + std::to_string(legs);
    }
};

int main() {
    Animal* a = new Snake();
    std::cout << a->describe() << "\n";
    delete a;
    return 0;
}
```

A. Animal legs=4  
B. Animal legs=0  
C. Snake legs=0  
D. 编译错误，派生类不能访问基类 protected 成员

<!--
Snake 在构造函数中把继承来的 protected 成员 legs 置为 0（合法）。
describe() 是 virtual，Animal* 指向 Snake 对象时动态分派到 Snake::describe()。
Snake::describe() 读取 legs（此时为 0），输出 "Snake legs=0"。
-->

## 解析

C 正确：`Snake` 可以访问并修改继承来的 `protected` 成员 `legs`，构造时把它设为 0。`describe` 是虚函数，`Animal*` 指向 `Snake` 时动态分派到 `Snake::describe`。关键误区是认为 `protected` 成员派生类不能访问，或忽略虚函数分派。
