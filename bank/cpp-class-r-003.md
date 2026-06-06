---
qid: cpp-class-r-003
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: D
---

# 代码阅读：const 成员函数修改非 mutable 成员

下列代码能否编译？

```cpp
struct Box {
    int value;
    mutable int cache;

    void set(int v) const {
        value = v;   // 行 A
        cache = v;   // 行 B
    }
};
```

A. 两行均合法：`const` 函数只禁止修改指针本身  
B. 行 A 合法，行 B 非法：`mutable` 成员不能在 `const` 函数中修改  
C. 两行均合法：`mutable` 豁免了整个函数的 `const` 限制  
D. 行 A 非法（`const` 函数不能修改普通成员），行 B 合法（`mutable` 成员可修改）

## 解析

正确答案为 D，因为“行 A 非法（`const` 函数不能修改普通成员），行 B 合法（`mutable` 成员可修改）”符合题干所问的 C++ 规则或代码执行结果。A、B、C 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
