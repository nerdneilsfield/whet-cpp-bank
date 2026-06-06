---
qid: cpp-prog-conc-mutex-counter-001
type: prog
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-conc-mutex-counter-001/
---
实现线程安全的 Counter 类，使用 std::mutex 保护 increment() 和 get()。启动 4 个线程各增加 10000 次，期望值 40000。

### 函数签名
```cpp
#pragma once
#include <mutex>

class Counter {
public:
    void increment();
    int get() const;
private:
    mutable std::mutex mtx_;
    int val_ = 0;
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

`increment()` 和 `get()` 都要在同一把 mutex 下访问 `val_`，这样读写不会发生数据竞争。递增时用 `std::lock_guard` 包住 `++val_`，读取时同样加锁后返回副本。常见错误是只保护写不保护读，测试在并发下仍可能观察到未同步访问。
