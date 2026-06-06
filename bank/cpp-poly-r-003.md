---
qid: cpp-poly-r-003
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: "D"
---

## 题目

以下代码能否通过编译？

```cpp
struct Shape {
    virtual double area() = 0;
};

int main() {
    Shape s;
    return 0;
}
```

A. 能编译，`area()` 返回默认值 0.0
B. 能编译，但调用 `s.area()` 时崩溃
C. 能编译，行为未定义
D. 编译错误，不能实例化抽象类

## 解析

`area()` 是纯虚函数（`= 0`），`Shape` 因此成为**抽象类**。抽象类不能直接实例化，编译器会报错：`cannot declare variable 's' to be of abstract type 'Shape'`。必须通过派生类提供 `area()` 的实现后才能创建对象。
