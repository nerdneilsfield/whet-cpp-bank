#pragma once
#include <functional>
#include <utility>

class ScopeExit {
public:
    template <class F>
    explicit ScopeExit(F&& f) : f_(std::forward<F>(f)), active_(true) {}
    ~ScopeExit() {
        // TODO: implement
    }
    void dismiss() {
        // TODO: implement
    }
    ScopeExit(const ScopeExit&) = delete;
    ScopeExit& operator=(const ScopeExit&) = delete;
private:
    std::function<void()> f_;
    bool active_;
};
