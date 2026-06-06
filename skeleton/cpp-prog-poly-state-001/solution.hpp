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

class RedState;
class GreenState;
class YellowState;

class RedState : public State {
public:
    std::string color() const override { return "Red"; }
    int duration() const override { return 30; }
    std::unique_ptr<State> next() const override;
};

class GreenState : public State {
public:
    std::string color() const override { return "Green"; }
    int duration() const override { return 25; }
    std::unique_ptr<State> next() const override;
};

class YellowState : public State {
public:
    std::string color() const override { return "Yellow"; }
    int duration() const override { return 5; }
    std::unique_ptr<State> next() const override;
};

inline std::unique_ptr<State> RedState::next() const { return std::make_unique<GreenState>(); }
inline std::unique_ptr<State> GreenState::next() const { return std::make_unique<YellowState>(); }
inline std::unique_ptr<State> YellowState::next() const { return std::make_unique<RedState>(); }

class TrafficLight {
    std::unique_ptr<State> state_;
public:
    TrafficLight() : state_(std::make_unique<RedState>()) {}
    void advance() { state_ = state_->next(); }
    std::string current_color() const { return state_->color(); }
    int current_duration() const { return state_->duration(); }
};
