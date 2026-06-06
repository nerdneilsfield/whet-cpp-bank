---
qid: cpp-inh-r-003
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: "C"
---

## 题目

阅读以下代码，编译结果是什么？

```cpp
#include <iostream>

class Shape {
protected:
    int sides = 4;
};

class Square : public Shape {
public:
    void printSides() {
        std::cout << sides << std::endl;   // (1)
    }
};

int main() {
    Square sq;
    sq.printSides();
    std::cout << sq.sides << std::endl;    // (2)
}
```

A. 编译通过，输出两行 `4`
B. (1) 处编译错误，(2) 处正常
C. (2) 处编译错误，(1) 处正常
D. 两处都编译错误

## 解析

`protected` 成员在**派生类内部**可以访问，因此 (1) 在 `Square::printSides` 中访问 `sides` 合法。但在**类外部**（`main` 函数中），`protected` 成员不可访问，(2) 处 `sq.sides` 导致编译错误。
