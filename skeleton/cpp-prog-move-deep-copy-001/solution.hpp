#pragma once
#include <cstddef>
#include <algorithm>

class DeepCopy {
public:
    DeepCopy(std::size_t n, int val) : size_(n), data_(new int[n]) {
        std::fill(data_, data_ + n, val);
        ++alive_;
    }
    ~DeepCopy() {
        delete[] data_;
        --alive_;
    }
    DeepCopy(const DeepCopy& o) : size_(o.size_), data_(new int[o.size_]) {
        std::copy(o.data_, o.data_ + size_, data_);
        ++copy_cnt_;
        ++alive_;
    }
    DeepCopy(DeepCopy&& o) noexcept : size_(o.size_), data_(o.data_) {
        o.data_ = nullptr;
        o.size_ = 0;
        ++move_cnt_;
        ++alive_;
    }
    DeepCopy& operator=(const DeepCopy& o) {
        if (this != &o) {
            delete[] data_;
            size_ = o.size_;
            data_ = new int[size_];
            std::copy(o.data_, o.data_ + size_, data_);
            ++copy_cnt_;
        }
        return *this;
    }
    DeepCopy& operator=(DeepCopy&& o) noexcept {
        if (this != &o) {
            delete[] data_;
            size_ = o.size_;
            data_ = o.data_;
            o.data_ = nullptr;
            o.size_ = 0;
            ++move_cnt_;
        }
        return *this;
    }
    const int* data() const noexcept { return data_; }
    std::size_t size() const noexcept { return size_; }
    static int alive() noexcept { return alive_; }
    static int copy_count() noexcept { return copy_cnt_; }
    static int move_count() noexcept { return move_cnt_; }
    static void reset_counters() noexcept {
        alive_ = 0; copy_cnt_ = 0; move_cnt_ = 0;
    }
private:
    int* data_;
    std::size_t size_;
    inline static int alive_ = 0;
    inline static int copy_cnt_ = 0;
    inline static int move_cnt_ = 0;
};
