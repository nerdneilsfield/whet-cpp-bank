---
qid: cpp-class-017
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: A
---

以下代码中，`Circle::getR()` 在类外定义，其中 `::` 的作用是？

```cpp
double Circle::getR() const {
    return radius;
}
```

A. 指明 `getR` 是 `Circle` 类的成员函数
B. 访问 `Circle` 的静态变量
C. 表示继承关系
D. 调用父类构造函数

## 解析

正确答案为 A，因为“指明 `getR` 是 `Circle` 类的成员函数”符合题干所问的 C++ 规则或代码执行结果。B、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
