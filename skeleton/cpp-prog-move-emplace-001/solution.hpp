#pragma once
#include <cstddef>
#include <utility>
#include <algorithm>

template <typename T>
class Container {
public:
    Container() : data_(nullptr), size_(0), cap_(0) {}
    ~Container() {
        for (std::size_t i = 0; i < size_; ++i) data_[i].~T();
        ::operator delete[](data_);
    }
    template <typename... Args>
    T& emplace_back(Args&&... args) {
        if (size_ == cap_) grow();
        ::new (&data_[size_]) T(std::forward<Args>(args)...);
        return data_[size_++];
    }
    std::size_t size() const noexcept { return size_; }
    T& operator[](std::size_t i) { return data_[i]; }
    const T& operator[](std::size_t i) const { return data_[i]; }
private:
    void grow() {
        std::size_t new_cap = cap_ == 0 ? 1 : cap_ * 2;
        T* new_data = static_cast<T*>(::operator new[](new_cap * sizeof(T)));
        for (std::size_t i = 0; i < size_; ++i)
            ::new (&new_data[i]) T(std::move(data_[i]));
        for (std::size_t i = 0; i < size_; ++i) data_[i].~T();
        ::operator delete[](data_);
        data_ = new_data;
        cap_ = new_cap;
    }
    T* data_;
    std::size_t size_;
    std::size_t cap_;
};
