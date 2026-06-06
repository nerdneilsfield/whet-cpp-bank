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

## 解析
维护 `data_`、`size_`、`cap_` 三个不变量：容量足够时直接写入，否则扩容并搬迁旧元素。拷贝构造/赋值要分配新数组并复制元素，移动构造/赋值转移指针与大小容量后把源对象清空。`push_back` 常用容量翻倍策略，空容量时先扩到 1；下标访问按签名返回引用。
