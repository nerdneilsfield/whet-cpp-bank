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

## 解析

正确答案是 A, C, D。A 项 ``Shape` 是抽象类，不能写 `Shape s;`` 符合规则；C 项 ``Shape* p = new Circle(1.0);` 合法` 符合规则；D 项 ``p->area()` 会动态分派到 `Circle::area()`` 符合规则；B 项 ``Shape* p = new Shape();` 合法` 不满足该规则。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 多选题常见误区是只看关键字相似就勾选，而没有逐项检查它是否真的满足题干条件。
