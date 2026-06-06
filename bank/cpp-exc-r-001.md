---
qid: cpp-exc-r-001
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: C
---

## 题目

下面代码运行时会发生什么？

```cpp
#include <iostream>

void risky() noexcept {
    throw std::runtime_error("oops");
}

int main() {
    try {
        risky();
    } catch (...) {
        std::cout << "caught\n";
    }
}
```

A. 输出 `caught`
B. `catch` 捕获异常，程序正常退出
C. 调用 `std::terminate`，程序终止
D. 编译错误：`noexcept` 函数中不能使用 `throw`

## 答案

C

## 解析

`noexcept` 声明告知编译器和调用者该函数不会抛出异常。若 `noexcept` 函数内部抛出了异常，C++ 标准规定直接调用 `std::terminate()`，**不会**进行栈展开，`try/catch` 也无法拦截。编译器允许在 `noexcept` 函数内写 `throw`（编译不报错），但运行时一旦真正抛出就立即终止程序。
