#pragma once
#include <atomic>

class Counter {
public:
    Counter() : n_(0) {}
    void inc() {
        // TODO: implement
    }
    int get() const {
        // TODO: implement
        return 0;
    }
private:
    std::atomic<int> n_;
};
