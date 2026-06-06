---
qid: cpp-ub-r-002
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

## 题目

下面代码的输出是什么？

```cpp
#include <iostream>
#include <string>

const std::string& get() {
    std::string local = "oops";
    return local;
}

int main() {
    const std::string& ref = get();
    std::cout << ref << std::endl;
    return 0;
}
```

A. 输出 `oops`
B. 输出空字符串
C. 返回局部变量引用，`ref` 是悬空引用，行为未定义
D. 编译错误，不能返回局部变量的引用

## 答案

C

## 解析

`get()` 返回局部变量 `local` 的引用。函数返回后，`local` 被销毁，`ref` 成为**悬空引用（dangling reference）**。通过悬空引用访问内存是**未定义行为**：程序可能输出垃圾值、崩溃，或偶然"正确"输出（恰好内存未被覆盖）。编译器通常会给出警告（`-Wreturn-local-addr`），但不是错误。
