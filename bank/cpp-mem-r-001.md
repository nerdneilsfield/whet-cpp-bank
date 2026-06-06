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

`std::move(p)` 将 `p` 的所有权转移给 `q`，之后 `p` 被置为 `nullptr`（`unique_ptr` 的移动构造函数保证这一点）。`*q` 正常访问 42。输出 `1 42`。
