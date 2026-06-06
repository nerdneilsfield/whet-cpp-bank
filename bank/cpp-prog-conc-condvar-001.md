---
qid: cpp-prog-conc-condvar-001
type: prog
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-conc-condvar-001/
---
实现有界缓冲区 BoundedBuffer，使用 std::mutex + std::condition_variable 同步生产者和消费者。支持 push()/pop()/size()。

## 函数签名
```cpp
#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

class BoundedBuffer {
public:
    explicit BoundedBuffer(std::size_t max_size);
    void push(int item);
    int pop();
    std::size_t size() const;
private:
    std::queue<int> queue_;
    mutable std::mutex mtx_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    std::size_t max_size_;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数