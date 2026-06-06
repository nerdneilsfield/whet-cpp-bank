---
qid: cpp-prog-move-deep-copy-001
type: prog
kp: [cpp-move-semantics]
primary_kp: cpp-move-semantics
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-move-deep-copy-001/
---
DeepCopy 类拥有 raw int* 和 size。实现拷贝构造/赋值（深拷贝）、移动构造/赋值（转移所有权）和析构。用静态计数器跟踪存活对象和拷贝次数。

## 函数签名
```cpp
#pragma once
#include <cstddef>

class DeepCopy {
public:
    DeepCopy(std::size_t n, int val);
    ~DeepCopy();
    DeepCopy(const DeepCopy& o);
    DeepCopy(DeepCopy&& o) noexcept;
    DeepCopy& operator=(const DeepCopy& o);
    DeepCopy& operator=(DeepCopy&& o) noexcept;
    const int* data() const noexcept;
    std::size_t size() const noexcept;
    static int alive() noexcept;
    static int copy_count() noexcept;
    static int move_count() noexcept;
    static void reset_counters() noexcept;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数