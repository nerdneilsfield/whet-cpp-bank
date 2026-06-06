#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& msg) = 0;
};

class Subject {
    std::vector<Observer*> obs_;
public:
    void attach(Observer* o) { obs_.push_back(o); }
    void detach(Observer* o) {
        obs_.erase(std::remove(obs_.begin(), obs_.end(), o), obs_.end());
    }
    void notify(const std::string& msg) {
        for (auto* o : obs_) o->update(msg);
    }
};
