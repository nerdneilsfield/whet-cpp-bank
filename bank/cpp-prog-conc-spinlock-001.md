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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

`lock()` 应循环调用 `flag_.test_and_set(std::memory_order_acquire)`，直到成功获得锁；`unlock()` 用 `clear(std::memory_order_release)` 释放。acquire/release 保证临界区内的读写不会越过锁边界。注意自旋锁只适合极短临界区，忘记在类内初始化 `atomic_flag` 会导致行为错误。
