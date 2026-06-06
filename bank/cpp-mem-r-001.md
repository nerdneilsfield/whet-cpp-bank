---
qid: cpp-mem-r-001
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "B"
---

## 题目

阅读以下代码，执行后 `p` 和 `q` 分别是什么状态？

```cpp
#include <memory>
#include <iostream>

int main() {
    auto p = std::make_unique<int>(42);
    auto q = std::move(p);
    std::cout << (p == nullptr) << " " << *q << std::endl;
}
```

A. `p` 仍指向 42，`q` 也指向 42（两个指针共享所有权）
B. `p` 变为 `nullptr`，`q` 指向 42，输出 `1 42`
C. 编译错误，`unique_ptr` 不能移动
D. 未定义行为，移动后 `p` 的值不确定

## 解析

正确答案是 B，`std::move(p)` 将 `unique_ptr` 的独占所有权转移给 `q`。移动后源 `unique_ptr` 按标准保证为空，因此 `p == nullptr` 为真，`q` 仍指向值为 42 的对象。常见误区是把 `unique_ptr` 当成共享所有权；它不会让两个指针同时拥有同一对象。
