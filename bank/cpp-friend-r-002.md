---
qid: cpp-friend-r-002
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: "A"
---

## 题目

阅读以下代码，程序输出是什么？

```cpp
#include <iostream>

class Base {
    int secret = 99;
    friend void peek(const Base& b);
};

class Derived : public Base {
public:
    void show() {
        // 尝试访问 Base 的 private 成员
        // std::cout << secret << std::endl;  // 假设此行取消注释
    }
};

void peek(const Base& b) {
    std::cout << b.secret << std::endl;
}

int main() {
    Derived d;
    peek(d);          // 传入 Derived 对象，隐式转换为 const Base&
}
```

A. `99`
B. 编译错误：`peek` 不能访问 `Derived` 对象的成员
C. `0`
D. 编译错误：friend 关系不能传给派生类对象

## 解析

`peek` 是 `Base` 的 friend，可以访问 `Base` 的 private 成员 `secret`。`Derived` 对象传入时隐式转换为 `const Base&`，`peek` 正常访问 `Base` 部分的 `secret`，输出 `99`。注意：friend 关系**不被继承**——`Derived` 的成员函数（如 `show`）不能访问 `Base::secret`，但 `peek` 本身仍有效。
