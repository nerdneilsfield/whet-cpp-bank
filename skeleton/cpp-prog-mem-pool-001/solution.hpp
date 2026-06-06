#pragma once
#include <array>
#include <vector>
#include <new>
#include <type_traits>

template <class T, int N>
class ObjectPool {
public:
    ObjectPool() {
        for (int i = N - 1; i >= 0; --i) free_idx_.push_back(i);
    }
    ~ObjectPool() {}
    T* acquire() {
        // TODO: implement (pop free_idx_, placement-new at slot)
        return nullptr;
    }
    void release(T* p) {
        (void)p;
        // TODO: implement (call destructor, push back index)
    }
private:
    alignas(T) unsigned char storage_[sizeof(T) * N];
    std::vector<int> free_idx_;
};
