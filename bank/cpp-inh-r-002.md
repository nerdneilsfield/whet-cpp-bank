---
qid: cpp-inh-r-002
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: "B"
---

## 题目

阅读以下代码，程序输出是什么？

```cpp
#include <iostream>

class Base {
public:
    Base() { std::cout << "Base()" << std::endl; }
    ~Base() { std::cout << "~Base()" << std::endl; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "Derived()" << std::endl; }
    ~Derived() { std::cout << "~Derived()" << std::endl; }
};

int main() {
    Derived d;
}
```

A. `Derived()` → `Base()` → `~Base()` → `~Derived()`
B. `Base()` → `Derived()` → `~Derived()` → `~Base()`
C. `Base()` → `Derived()` → `~Base()` → `~Derived()`
D. `Derived()` → `Base()` → `~Derived()` → `~Base()`

## 解析

构造顺序：**基类先于派生类**——`Base()` 先执行，再执行 `Derived()`。析构顺序与构造顺序相反：`~Derived()` 先执行，再执行 `~Base()`。输出顺序为 B 所示。
