#pragma once
#include <cstddef>
#include <utility>
#include <algorithm>

class IntArray {
public:
    IntArray(std::size_t n, int v) : data_(new int[n]), n_(n) {
        for (std::size_t i = 0; i < n; ++i) data_[i] = v;
    }
    ~IntArray() { delete[] data_; }
    IntArray(const IntArray& o) : data_(nullptr), n_(0) {
        (void)o;
        // TODO: implement
    }
    IntArray(IntArray&& o) noexcept : data_(nullptr), n_(0) {
        (void)o;
        // TODO: implement
    }
    IntArray& operator=(const IntArray& o) {
        (void)o;
        // TODO: implement
        return *this;
    }
    IntArray& operator=(IntArray&& o) noexcept {
        (void)o;
        // TODO: implement
        return *this;
    }
    std::size_t size() const noexcept { return n_; }
    int at(std::size_t i) const { return data_[i]; }
private:
    int* data_;
    std::size_t n_;
};
