---
qid: cpp-class-020
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: D
---

以下结构体聚合初始化，哪项是正确的？

```cpp
struct Point {
    int x;
    int y;
};
```

A. `Point p = Point(1, 2);`
B. `Point p; p = {1, 2};`（仅 C++11 之前）
C. `Point p(1, 2);`
D. `Point p = {1, 2};`

## Explanation

正确答案为 D，因为“`Point p = {1, 2};`”符合题干所问的 C++ 规则或代码执行结果。A、B、C 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
