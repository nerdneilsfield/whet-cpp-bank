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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

该类拥有裸指针，因此必须按 Rule of Five 管理资源：拷贝构造和拷贝赋值分配新数组并复制内容，移动构造和移动赋值转移指针后把源对象置空。析构只释放当前拥有的数组，赋值要处理自赋值并避免泄漏旧资源。计数器应在对应构造、析构、拷贝和移动路径中准确更新。
