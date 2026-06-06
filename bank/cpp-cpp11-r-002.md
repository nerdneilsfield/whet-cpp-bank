---
qid: cpp-cpp11-r-002
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: "C"
---

### 题目

阅读以下委托构造函数代码，程序输出是什么？

```cpp
#include <iostream>

struct Foo {
    Foo() : Foo(0) {
        std::cout << "A";
    }
    Foo(int n) : Foo(n, 0) {
        std::cout << "B";
    }
    Foo(int n, int m) {
        std::cout << "C";
    }
};

int main() {
    Foo f;
}
```

A. `ABC`
B. `CBA`
C. `CBA`
D. `BAC`

## Explanation

委托构造函数的执行顺序：先执行**被委托**的构造函数体，再执行**委托者**的构造函数体。`Foo()` 委托 `Foo(int)`，`Foo(int)` 委托 `Foo(int,int)`。调用链：`Foo(int,int)` 体先执行输出 `C`，返回后 `Foo(int)` 体执行输出 `B`，再返回后 `Foo()` 体执行输出 `A`。最终输出 `CBA`。
