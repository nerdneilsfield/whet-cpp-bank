---
qid: cpp-prog-conc-spsc-001
type: prog
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
toolchain: [make]
tests_dir: tests/cpp-prog-conc-spsc-001/
---
实现 SPSC（单生产单消费）环形缓冲：push(x) 满返回 false，pop(out) 空返回 false。使用 std::atomic 索引。容量 N 编译期固定。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <atomic>
#include <array>

template <class T, std::size_t N>
class SPSCQueue {
public:
    SPSCQueue();
    bool push(const T& v);
    bool pop(T& out);
private:
    std::array<T, N> buf_;
    std::atomic<std::size_t> head_;
    std::atomic<std::size_t> tail_;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数