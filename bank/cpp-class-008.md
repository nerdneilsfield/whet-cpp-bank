---
qid: cpp-class-008
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: B
---

以下哪种方式在**堆**上创建一个 `Point` 对象？

A. `Point p;`
B. `Point* p = new Point();`
C. `Point& p = Point();`
D. `Point p = Point{};`

## Explanation

正确答案为 B，因为“`Point* p = new Point();`”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
