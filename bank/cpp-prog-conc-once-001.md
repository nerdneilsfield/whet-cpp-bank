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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

应在类中使用 `std::once_flag` 配合 `std::call_once` 包住真正初始化逻辑，确保多线程同时调用时初始化函数只执行一次。初始化逻辑内部设置 `initialized_` 并递增 `init_cnt_`，查询函数用 mutex 或原子方式安全读取状态。注意仅靠普通 bool 双重检查不够安全，`call_once` 才提供所需的同步保证。
