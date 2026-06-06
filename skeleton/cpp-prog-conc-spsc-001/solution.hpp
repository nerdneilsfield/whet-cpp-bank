#pragma once
#include <atomic>
#include <array>

template <class T, std::size_t N>
class SPSCQueue {
public:
    SPSCQueue() : head_(0), tail_(0) {}
    bool push(const T& v) {
        (void)v;
        // TODO: implement
        return false;
    }
    bool pop(T& out) {
        (void)out;
        // TODO: implement
        return false;
    }
private:
    std::array<T, N> buf_;
    std::atomic<std::size_t> head_;
    std::atomic<std::size_t> tail_;
};
