---
qid: cpp-exc-r-003
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: B
---

## 题目

下面代码的输出是什么？

```cpp
#include <iostream>

struct Guard {
    ~Guard() { std::cout << "~Guard\n"; }
};

void foo() {
    Guard g;
    throw std::runtime_error("err");
}

int main() {
    try {
        foo();
    } catch (const std::exception& e) {
        std::cout << "caught: " << e.what() << "\n";
    }
}
```

A. caught: err
B. ~Guard  然后  caught: err
C. caught: err  然后  ~Guard
D. 程序终止，无输出

## 答案

B

## 解析

C++ 异常机制在传播异常时会执行**栈展开（stack unwinding）**：退出作用域时，该作用域内所有已构造的局部对象的析构函数按构造的逆序调用。`foo()` 中 `g` 是局部对象，抛出异常时栈展开先调用 `~Guard`，再把控制权交给 `catch` 块，因此输出顺序是先 `~Guard` 再 `caught: err`。
