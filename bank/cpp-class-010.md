---
qid: cpp-class-010
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: C
---

访问指针所指对象的成员，应使用哪个操作符？

```cpp
Point* p = new Point();
// 访问 p 指向对象的 x 成员
```

A. `p.x`
B. `p::x`
C. `p->x`
D. `*p::x`

## 解析

正确答案为 C，因为“`p->x`”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
