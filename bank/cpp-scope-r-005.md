---
qid: cpp-scope-r-005
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: B
---

## 题目

下面代码的输出是什么？（假设平台上 `int` 为 4 字节）

```cpp
#include <iostream>

int g;   // 全局变量

int main() {
    int l;   // 局部变量，未初始化
    std::cout << g << "\n";
    // std::cout << l << "\n";  // 故意注释掉，避免 UB
    g = 99;
    std::cout << g << "\n";
}
```

A. 未定义行为，输出随机值
B. 输出 0，然后 99
C. 编译错误：全局变量必须显式初始化
D. 输出 0，然后 0

## 答案

B

## 解析

**全局变量**（静态存储期变量）在程序启动时由运行时系统零初始化：`int` 类型初始化为 `0`，指针初始化为 `nullptr`，等等。**局部变量**（自动存储期）不被零初始化，读取未初始化的局部变量是未定义行为（这也是代码中注释掉 `l` 的原因）。
