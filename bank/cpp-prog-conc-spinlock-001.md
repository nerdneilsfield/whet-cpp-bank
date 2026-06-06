---
qid: cpp-prog-conc-spinlock-001
type: prog
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-conc-spinlock-001/
---
用 std::atomic_flag 实现 Spinlock。提供 lock() / unlock()。测试：两个线程各递增一个共享计数器 5000 次。

## 函数签名
```cpp
#pragma once
#include <atomic>

class Spinlock {
public:
    void lock();
    void unlock();
private:
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数