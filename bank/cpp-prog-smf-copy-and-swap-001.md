---
qid: cpp-prog-smf-copy-and-swap-001
type: prog
kp: [cpp-special-members]
primary_kp: cpp-special-members
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-smf-copy-and-swap-001/
---
实现 CopyAndSwap 类（拥有 char* 动态缓冲区）使用 copy-and-swap 惯用法统一处理拷贝赋值和移动赋值。

## 函数签名
```cpp
#pragma once
#include <cstddef>
#include <utility>

class CopyAndSwap {
public:
    CopyAndSwap();
    CopyAndSwap(const char* s);
    ~CopyAndSwap();
    CopyAndSwap(const CopyAndSwap& o);
    CopyAndSwap(CopyAndSwap&& o) noexcept;
    CopyAndSwap& operator=(CopyAndSwap o) noexcept;  // copy-and-swap
    friend void swap(CopyAndSwap& a, CopyAndSwap& b) noexcept;
    const char* c_str() const noexcept;
    std::size_t size() const noexcept;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数