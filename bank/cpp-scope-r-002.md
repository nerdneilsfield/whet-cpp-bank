---
qid: cpp-scope-r-002
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: A
---

## 题目

下面代码的输出是什么？

```cpp
#include <iostream>

int x = 10;

int main() {
    int x = 20;
    {
        int x = 30;
        std::cout << x << "\n";
    }
    std::cout << x << "\n";
    std::cout << ::x << "\n";
}
```

A. 30 20 10
B. 10 20 30
C. 30 30 10
D. 编译错误

## 答案

A

## 解析

内层块中的局部变量 `x = 30` 遮蔽了外层的同名变量，块结束后恢复到函数体内的 `x = 20`。`::x` 使用全局作用域限定符，访问全局变量 `x = 10`。内层遮蔽不会修改外层变量的值。
