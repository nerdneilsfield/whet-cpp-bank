---
qid: cpp-poly-018
type: multi
kp: [cpp-polymorphism]
difficulty: easy
answer_key: [A, C, D]
---

# 以下哪些说法是正确的？（多选）

```cpp
struct Shape {
    virtual double area() = 0;
    virtual ~Shape() = default;
};
struct Circle : Shape {
    double r;
    Circle(double r) : r(r) {}
    double area() override { return 3.14 * r * r; }
};
```

A. `Shape` 是抽象类，不能写 `Shape s;`  
B. `Shape* p = new Shape();` 合法  
C. `Shape* p = new Circle(1.0);` 合法  
D. `p->area()` 会动态分派到 `Circle::area()`  
E. `~Shape()` 不需要是 `virtual`，因为已经是 `default`
