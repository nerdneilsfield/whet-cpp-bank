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

## 函数签名
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

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数