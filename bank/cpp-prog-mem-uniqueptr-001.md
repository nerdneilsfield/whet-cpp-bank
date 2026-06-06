---
qid: cpp-prog-mem-uniqueptr-001
type: prog
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-mem-uniqueptr-001/
---
实现简化版 UniquePtr<T>：独占所有权，move 转移，析构 delete。支持 operator*, operator->, get(), release(), reset()。禁拷贝。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <utility>

template <class T>
class UniquePtr {
public:
    UniquePtr() noexcept;
    explicit UniquePtr(T* p) noexcept;
    ~UniquePtr();
    UniquePtr(UniquePtr&& other) noexcept;
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    T& operator*() const;
    T* operator->() const noexcept;
    T* get() const noexcept;
    T* release() noexcept;
    void reset(T* p = nullptr) noexcept;
    explicit operator bool() const noexcept;
private:
    T* ptr_;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数