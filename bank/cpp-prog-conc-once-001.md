---
qid: cpp-prog-conc-once-001
type: prog
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-conc-once-001/
---
使用 std::call_once 实现 LazyInit 类，保证 init() 只被执行一次。多个线程同时触发 init，检查计数器验证只调用一次。

## 函数签名
```cpp
#pragma once
#include <mutex>

class LazyInit {
public:
    void ensure_init();
    bool is_initialized() const;
    int init_count() const;
private:
    mutable std::mutex mtx_;
    bool initialized_ = false;
    int init_cnt_ = 0;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数