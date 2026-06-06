---
qid: cpp-class-r-004
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: B
---

# 代码阅读：析构顺序（先派生后基类）

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
struct Base {
    ~Base() { std::cout << "~Base "; }
};
struct Derived : Base {
    ~Derived() { std::cout << "~Derived "; }
};
int main() {
    Derived d;
    return 0;
}
```

A. `~Base ~Derived`  
B. `~Derived ~Base`  
C. 仅输出 `~Base`（`Derived` 析构函数未设为 `virtual`）  
D. 编译错误：析构函数必须声明为 `virtual`

## Explanation

正确答案为 B，因为“`~Derived ~Base`”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
