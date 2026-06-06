---
qid: cpp-cpp11-r-005
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: "C"
---

### 题目

阅读以下代码，`f(nullptr)` 调用的是哪个重载？

```cpp
#include <iostream>

void f(int* p)  { std::cout << "ptr"; }
void f(int n)   { std::cout << "int"; }

int main() {
    f(nullptr);  // 调用哪个重载？
    // f(0);     // 若改为 f(0) 又如何？
}
```

A. 调用 `f(int)`，输出 `int`
B. 编译错误：歧义，两个重载均匹配
C. 调用 `f(int*)`，输出 `ptr`
D. 调用 `f(int)`，但行为未定义

## Explanation

C++11 引入 `nullptr`，类型为 `std::nullptr_t`，可隐式转换为任何指针类型，但**不能**隐式转换为整数类型（`int`）。因此 `f(nullptr)` 唯一匹配 `f(int*)`，输出 `ptr`。若改为 `f(0)`，字面量 `0` 既可转 `int*` 又可转 `int`，编译器会报歧义错误（或在某些编译器中优先选 `int`）。`nullptr` 的设计正是为了消除这种歧义。
