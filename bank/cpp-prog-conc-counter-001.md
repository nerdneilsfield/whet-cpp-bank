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

## 解析
计数器内部用 `std::atomic<int>` 保存值，构造时初始化为 0。`inc()` 使用原子自增，`get()` 使用原子 load 返回当前值，多个线程并发调用不会丢失更新。若只要求计数正确，不涉及额外同步关系，默认顺序或 relaxed 都能满足数值原子性。
