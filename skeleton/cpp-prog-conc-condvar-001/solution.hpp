#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

class BoundedBuffer {
    std::queue<int> queue_;
    mutable std::mutex mtx_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    std::size_t max_size_;
public:
    explicit BoundedBuffer(std::size_t max_size) : max_size_(max_size) {}
    void push(int item) {
        std::unique_lock<std::mutex> lk(mtx_);
        not_full_.wait(lk, [this]() { return queue_.size() < max_size_; });
        queue_.push(item);
        not_empty_.notify_one();
    }
    int pop() {
        std::unique_lock<std::mutex> lk(mtx_);
        not_empty_.wait(lk, [this]() { return !queue_.empty(); });
        int val = queue_.front();
        queue_.pop();
        not_full_.notify_one();
        return val;
    }
    std::size_t size() const {
        std::lock_guard<std::mutex> lk(mtx_);
        return queue_.size();
    }
};
