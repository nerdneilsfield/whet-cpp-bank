---
qid: cpp-class-r-005
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: C
---

# 代码阅读：对象按值传参触发拷贝构造

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
struct Widget {
    Widget() { std::cout << "ctor "; }
    Widget(const Widget&) { std::cout << "copy "; }
    ~Widget() { std::cout << "dtor "; }
};
void use(Widget w) {}
int main() {
    Widget a;
    use(a);
    return 0;
}
```

A. `ctor dtor dtor`  
B. `ctor copy dtor`  
C. `ctor copy dtor dtor`  
D. `ctor dtor`

## 解析

正确答案为 C，因为“`ctor copy dtor dtor`”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
