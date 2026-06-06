---
qid: cpp-prog-move-vector-001
type: prog
kp: [cpp-move-semantics]
primary_kp: cpp-move-semantics
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-move-vector-001/
---
实现最小化 Vector：构造、析构、拷贝构造/赋值、移动构造/赋值、push_back、size、operator[]。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <cstddef>
#include <utility>

class Vector {
public:
    Vector();
    ~Vector();
    Vector(const Vector& o);
    Vector(Vector&& o) noexcept;
    Vector& operator=(const Vector& o);
    Vector& operator=(Vector&& o) noexcept;
    void push_back(int x);
    std::size_t size() const noexcept;
    int& operator[](std::size_t i);
    const int& operator[](std::size_t i) const;
private:
    int* data_;
    std::size_t size_;
    std::size_t cap_;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数