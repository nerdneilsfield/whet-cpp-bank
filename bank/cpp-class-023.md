---
qid: cpp-class-023
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: A
---

下列代码的输出是什么？

```cpp
#include <iostream>
class Counter {
public:
    static int count;
    Counter() { count++; }
};
int Counter::count = 0;
int main() {
    Counter a, b, c;
    std::cout << Counter::count;
}
```

A. `3`
B. `0`
C. `1`
D. 编译错误

## Explanation

正确答案为 A，因为“`3`”符合题干所问的 C++ 规则或代码执行结果。B、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
