---
qid: cpp-inh-r-004
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: "B"
---

## 题目

阅读以下代码，编译结果是什么？

```cpp
#include <iostream>

class Engine {
public:
    void start() { std::cout << "Engine started" << std::endl; }
    void stop()  { std::cout << "Engine stopped" << std::endl; }
};

class Car : private Engine {      // private 继承
public:
    void run() { start(); }       // OK：在类内部可以访问
};

int main() {
    Car c;
    c.run();           // (1)
    c.start();         // (2)
}
```

A. 编译通过，输出两行
B. (2) 处编译错误，(1) 处正常
C. (1) 处编译错误，(2) 处正常
D. 两处都编译错误

## 解析

`private` 继承使 `Engine` 的所有 `public` 成员（包括 `start`、`stop`）在 `Car` 的**类外部**变为 `private`。在 `Car` 的成员函数内仍可调用，所以 (1) `c.run()` 合法。但外部直接调用 `c.start()` 即 (2) 违反访问控制，编译错误。
