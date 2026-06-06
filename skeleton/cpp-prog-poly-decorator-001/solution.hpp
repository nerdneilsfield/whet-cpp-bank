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
    double cost() const override { return 1.0; }
    std::string description() const override { return "Espresso"; }
};

class Decorator : public Beverage {
protected:
    std::unique_ptr<Beverage> wrapped_;
public:
    explicit Decorator(std::unique_ptr<Beverage> b) : wrapped_(std::move(b)) {}
};

class MilkDecorator : public Decorator {
public:
    using Decorator::Decorator;
    double cost() const override { return wrapped_->cost() + 0.5; }
    std::string description() const override { return wrapped_->description() + " + Milk"; }
};

class SugarDecorator : public Decorator {
public:
    using Decorator::Decorator;
    double cost() const override { return wrapped_->cost() + 0.2; }
    std::string description() const override { return wrapped_->description() + " + Sugar"; }
};
