#pragma once
#include <cstddef>
#include <cstring>
#include <utility>

class CopyAndSwap {
public:
    CopyAndSwap() : data_(nullptr), size_(0) {}
    CopyAndSwap(const char* s) : data_(nullptr), size_(std::strlen(s)) {
        if (size_) {
            data_ = new char[size_ + 1];
            std::memcpy(data_, s, size_ + 1);
        }
    }
    ~CopyAndSwap() { delete[] data_; }
    CopyAndSwap(const CopyAndSwap& o) : data_(nullptr), size_(o.size_) {
        if (size_) {
            data_ = new char[size_ + 1];
            std::memcpy(data_, o.data_, size_ + 1);
        }
    }
    CopyAndSwap(CopyAndSwap&& o) noexcept : data_(o.data_), size_(o.size_) {
        o.data_ = nullptr;
        o.size_ = 0;
    }
    CopyAndSwap& operator=(CopyAndSwap o) noexcept {
        swap(*this, o);
        return *this;
    }
    friend void swap(CopyAndSwap& a, CopyAndSwap& b) noexcept {
        using std::swap;
        swap(a.data_, b.data_);
        swap(a.size_, b.size_);
    }
    const char* c_str() const noexcept { return data_ ? data_ : ""; }
    std::size_t size() const noexcept { return size_; }
private:
    char* data_;
    std::size_t size_;
};
