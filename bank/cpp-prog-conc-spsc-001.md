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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
SPSC 环形队列通常用 `head_` 表示消费位置，`tail_` 表示生产位置，并用取模推进索引。`push` 先计算 next tail，若等于 head 表示满；写入数据后发布 tail。`pop` 若 head 等于 tail 表示空，否则读出数据并推进 head；原子读写要使用合适的 acquire/release 顺序保证单生产单消费可见性。
