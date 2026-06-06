#pragma once
#include <utility>

template <class T>
class UniquePtr {
public:
    UniquePtr() noexcept : ptr_(nullptr) {}
    explicit UniquePtr(T* p) noexcept : ptr_(p) {}
    ~UniquePtr() { delete ptr_; }
    UniquePtr(UniquePtr&& other) noexcept : ptr_(nullptr) {
        (void)other;
        // TODO: implement
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        (void)other;
        // TODO: implement
        return *this;
    }
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    T& operator*() const { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    T* get() const noexcept { return ptr_; }
    T* release() noexcept {
        // TODO: implement
        return nullptr;
    }
    void reset(T* p = nullptr) noexcept {
        (void)p;
        // TODO: implement
    }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }
private:
    T* ptr_;
};
