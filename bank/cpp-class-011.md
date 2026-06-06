---
qid: cpp-class-011
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: A
---

成员初始化列表的正确写法是哪项？

```cpp
class Box {
    int w, h;
public:
    // 用初始化列表初始化 w=2, h=3
};
```

A. `Box() : w(2), h(3) {}`
B. `Box() { w(2); h(3); }`
C. `Box() = { w:2, h:3 };`
D. `Box() -> w(2), h(3) {}`

## 解析

正确答案为 A，因为“`Box() : w(2), h(3) {}`”符合题干所问的 C++ 规则或代码执行结果。B、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
