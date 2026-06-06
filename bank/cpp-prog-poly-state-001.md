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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

每个状态类实现自己的颜色、持续时间和 `next()`，`TrafficLight` 持有当前 `unique_ptr<State>`。`advance()` 用当前状态的 `next()` 替换状态指针，实现 Red、Green、Yellow 循环。注意 `next()` 要返回新对象而不是返回指向临时对象的裸指针。
