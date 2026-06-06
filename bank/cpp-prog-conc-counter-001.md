---
qid: cpp-prog-conc-counter-001
type: prog
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-conc-counter-001/
---
实现线程安全计数器 Counter：inc()、get()。要求多线程并发 inc 后 get 等于总次数。提示：std::atomic<int>。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <atomic>

class Counter {
public:
    Counter();
    void inc();
    int get() const;
private:
    std::atomic<int> n_;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数