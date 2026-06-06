---
qid: cpp-class-003
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: C
---

以下代码能否正确编译？

```cpp
class Dog {
    int age;
};
int main() {
    Dog d;
    d.age = 3;
}
```

A. 能，因为 `age` 是整型
B. 能，因为 `Dog` 是类
C. 不能，因为 `age` 默认是 `private`，外部无法访问
D. 不能，因为类定义缺少构造函数

## 解析

正确答案为 C，因为“不能，因为 `age` 默认是 `private`，外部无法访问”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
