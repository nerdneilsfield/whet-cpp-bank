---
qid: cpp-prog-poly-shape-001
type: prog
kp: [cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-poly-shape-001/
---
实现 Shape 基类（虚析构 + 纯虚 area()）和派生 Circle(r)、Rectangle(w,h)。total_area(v) 接收 vector<unique_ptr<Shape>>，返回面积之和。π 取 3.14159265358979。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>
#include <memory>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

class Circle : public Shape {
public:
    explicit Circle(double r);
    double area() const override;
private:
    double r_;
};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h);
    double area() const override;
private:
    double w_, h_;
};

double total_area(const std::vector<std::unique_ptr<Shape>>& shapes);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数