---
qid: cpp-real-en-026
type: single
kp: [cpp-classes, cpp-polymorphism]
primary_kp: cpp-classes
difficulty: easy
answer_key: C
tags: [interview-real, geeksforgeeks]
---
关于抽象类（abstract class）在 C++ 中的使用，以下说法正确的是？

A. 任何没有成员变量的类都是抽象类
B. 抽象类可以被实例化，只是部分函数没有实现
C. 包含至少一个纯虚函数（pure virtual function）的类即为抽象类，不能被实例化
D. 抽象类中不能有已实现的普通成员函数

---

**解析：**

- **抽象类**：包含**至少一个纯虚函数**的类。纯虚函数形式为 `virtual void func() = 0;`。
- **不能实例化**：抽象类不能创建对象。派生类必须实现所有纯虚函数才能被实例化，否则也是抽象类。
- **可以有普通函数**：抽象类完全可以包含已实现的成员函数、数据成员、构造函数/析构函数。
- **用途**：定义接口规范，强制派生类实现特定行为。

```cpp
class Shape {
public:
    virtual double area() = 0;  // 纯虚函数
    virtual ~Shape() = default;
};
// Shape s;  // 错误：不能实例化抽象类
class Circle : public Shape {
    double area() override { return 3.14 * r_ * r_; }
};
```

**来源：** GeeksforGeeks "Abstract Class in C++"