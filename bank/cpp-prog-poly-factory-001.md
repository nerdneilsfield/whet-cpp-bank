---
qid: cpp-prog-poly-factory-001
type: prog
kp: [cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-poly-factory-001/
---
实现 Shape 工厂模式：ShapeFactory::create(name) 根据字符串返回 Circle 或 Square（继承 Shape）。每个子类有 draw() 返回字符串描述。

## 函数签名
```cpp
#pragma once
#include <memory>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::string draw() const = 0;
};

class Circle : public Shape {
public:
    explicit Circle(double r);
    std::string draw() const override;
};

class Square : public Shape {
public:
    explicit Square(double s);
    std::string draw() const override;
};

class ShapeFactory {
public:
    static std::unique_ptr<Shape> create(const std::string& type, double param);
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数