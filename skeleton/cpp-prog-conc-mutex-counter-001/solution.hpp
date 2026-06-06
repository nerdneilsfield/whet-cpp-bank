#pragma once
#include <mutex>

class Counter {
    mutable std::mutex mtx_;
    int val_ = 0;
public:
    void increment() {
        std::lock_guard<std::mutex> lk(mtx_);
        ++val_;
    }
    int get() const {
        std::lock_guard<std::mutex> lk(mtx_);
        return val_;
    }
};
