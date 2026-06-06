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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

装饰器持有一个 `unique_ptr<Beverage>`，每个具体装饰器在调用被包装对象的 `cost()` 和 `description()` 基础上追加自己的价格与描述。Espresso 提供基础行为，Milk 和 Sugar 只增量修改。注意基类析构函数必须为 virtual，装饰器构造时要转移所有权而不是复制 `unique_ptr`。
