#pragma once
#include <cstddef>
#include <utility>
#include <algorithm>

class Vector {
public:
    Vector() : data_(nullptr), size_(0), cap_(0) {}
    ~Vector() { delete[] data_; }
    Vector(const Vector& o) : data_(nullptr), size_(0), cap_(0) {
        (void)o;
        // TODO: implement
    }
    Vector(Vector&& o) noexcept : data_(nullptr), size_(0), cap_(0) {
        (void)o;
        // TODO: implement
    }
    Vector& operator=(const Vector& o) {
        (void)o;
        // TODO: implement
        return *this;
    }
    Vector& operator=(Vector&& o) noexcept {
        (void)o;
        // TODO: implement
        return *this;
    }
    void push_back(int x) {
        (void)x;
        // TODO: implement
    }
    std::size_t size() const noexcept { return size_; }
    int& operator[](std::size_t i) { return data_[i]; }
    const int& operator[](std::size_t i) const { return data_[i]; }
private:
    int* data_;
    std::size_t size_;
    std::size_t cap_;
};
