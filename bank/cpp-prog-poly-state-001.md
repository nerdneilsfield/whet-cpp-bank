---
qid: cpp-prog-poly-state-001
type: prog
kp: [cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-poly-state-001/
---
TrafficLight 状态机使用多态 State。三个状态 Red -> Green -> Yellow -> Red。每个 State 有 duration() 和 next()。

## 函数签名
```cpp
#pragma once
#include <memory>
#include <string>

class State {
public:
    virtual ~State() = default;
    virtual std::string color() const = 0;
    virtual int duration() const = 0;
    virtual std::unique_ptr<State> next() const = 0;
};

class RedState : public State {
public:
    std::string color() const override;
    int duration() const override;
    std::unique_ptr<State> next() const override;
};

class GreenState : public State {
public:
    std::string color() const override;
    int duration() const override;
    std::unique_ptr<State> next() const override;
};

class YellowState : public State {
public:
    std::string color() const override;
    int duration() const override;
    std::unique_ptr<State> next() const override;
};

class TrafficLight {
public:
    TrafficLight();
    void advance();
    std::string current_color() const;
    int current_duration() const;
private:
    std::unique_ptr<State> state_;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数