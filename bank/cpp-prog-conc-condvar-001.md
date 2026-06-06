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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

核心是用同一个互斥锁保护队列和大小，并用 `not_full_`、`not_empty_` 分别等待可写和可读条件。`push` 在队列满时用带谓词的 `wait`，插入后通知消费者；`pop` 在队列空时等待，取出后通知生产者。注意 `size()` 也必须加锁，且等待要用谓词防止虚假唤醒。
