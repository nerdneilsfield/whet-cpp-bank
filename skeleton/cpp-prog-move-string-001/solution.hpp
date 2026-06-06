#pragma once
#include <cstddef>
#include <cstring>
#include <utility>

class String {
public:
    String() : data_(new char[1]{0}), size_(0) {}
    String(const char* s) : data_(nullptr), size_(0) {
        (void)s;
        // TODO: implement
        data_ = new char[1]{0};
    }
    ~String() { delete[] data_; }
    String(const String& o) : data_(nullptr), size_(0) {
        (void)o;
        // TODO: implement
        data_ = new char[1]{0};
    }
    String(String&& o) noexcept : data_(nullptr), size_(0) {
        (void)o;
        // TODO: implement
    }
    String& operator=(const String& o) {
        (void)o;
        // TODO: implement
        return *this;
    }
    String& operator=(String&& o) noexcept {
        (void)o;
        // TODO: implement
        return *this;
    }
    std::size_t size() const noexcept { return size_; }
    const char* c_str() const noexcept { return data_; }
private:
    char* data_;
    std::size_t size_;
};
