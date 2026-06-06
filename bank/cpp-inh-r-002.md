---
qid: cpp-inh-r-002
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: "B"
---

### 题目

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

## Explanation

正确答案是 B。构造派生类对象时会先构造基类子对象，再执行派生类构造函数，所以先输出 `Base()` 再输出 `Derived()`。对象销毁顺序与构造顺序相反，先调用 `~Derived()`，再调用 `~Base()`。A、C、D 都把构造或析构顺序颠倒了，这是继承题中最常见的误区。
