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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

copy-and-swap 的赋值运算符按值接收参数，调用时会先构造副本或移动临时对象，然后与当前对象交换资源。这样拷贝赋值和移动赋值共用一套逻辑，并天然具备较强异常安全性。注意析构释放当前缓冲区，swap 必须 noexcept，移动构造后源对象应处于可析构的空状态。
