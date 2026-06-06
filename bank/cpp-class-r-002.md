---
qid: cpp-class-r-002
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: B
---

# 代码阅读：静态成员跨对象共享

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
struct Counter {
    static int count;
    Counter() { ++count; }
};
int Counter::count = 0;

int main() {
    Counter a, b, c;
    std::cout << Counter::count;
    return 0;
}
```

A. `0`  
B. `3`  
C. 编译错误：`count` 未在类外定义  
D. 每个对象各有一份 `count`，输出 `1`

## 解析

正确答案为 B，因为“`3`”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
