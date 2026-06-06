---
qid: cpp-prog-design-rate-limit-001
type: prog
kp: [cpp-classes]
primary_kp: cpp-classes
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-design-rate-limit-001/
---
实现 TokenBucket 速率限制器。每秒 replenish N 个 token，每请求消耗 1 个 token。allow() 返回 true/false。

## 函数签名
```cpp
#pragma once
#include <chrono>

class TokenBucket {
public:
    TokenBucket(int rate, int burst);
    bool allow();
private:
    int rate_;
    int burst_;
    int tokens_;
    std::chrono::steady_clock::time_point last_refill_;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数