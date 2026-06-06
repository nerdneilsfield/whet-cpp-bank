---
qid: cpp-prog-poly-decorator-001
type: prog
kp: [cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-poly-decorator-001/
---
Coffee 装饰器模式：Beverage 是抽象基类（cost() + description()）。依次装饰 Espresso -> MilkDecorator -> SugarDecorator。

## 函数签名
```cpp
#pragma once
#include <string>
#include <memory>

class Beverage {
public:
    virtual ~Beverage() = default;
    virtual double cost() const = 0;
    virtual std::string description() const = 0;
};

class Espresso : public Beverage {
public:
    double cost() const override;
    std::string description() const override;
};

class Decorator : public Beverage {
protected:
    std::unique_ptr<Beverage> wrapped_;
public:
    explicit Decorator(std::unique_ptr<Beverage> b);
};

class MilkDecorator : public Decorator {
public:
    using Decorator::Decorator;
    double cost() const override;
    std::string description() const override;
};

class SugarDecorator : public Decorator {
public:
    using Decorator::Decorator;
    double cost() const override;
    std::string description() const override;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数