---
qid: cpp-smf-r-004
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: "C"
---

## 题目

阅读以下代码，运行后输出的析构顺序是什么？

```cpp
#include <iostream>

struct A { ~A() { std::cout << "~A\n"; } };
struct B { ~B() { std::cout << "~B\n"; } };
struct C { ~C() { std::cout << "~C\n"; } };

struct Obj {
    A a;
    B b;
    C c;
};

int main() {
    Obj obj;
}
```

A. `~A` → `~B` → `~C`
B. 顺序不确定
C. `~C` → `~B` → `~A`
D. `~Obj` → `~A` → `~B` → `~C`

## 解析

C++ 标准规定：成员对象按**声明顺序的逆序**析构。`Obj` 中成员声明顺序为 `a, b, c`，因此析构顺序为 `c → b → a`，输出 `~C`、`~B`、`~A`。这与构造顺序（`a → b → c`）完全相反，保证了资源的正确释放。
