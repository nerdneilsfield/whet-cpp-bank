---
qid: cpp-mem-010
type: fill
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "std::make_unique<int>(42)"
---

# 代码补全：创建 unique_ptr（C++14）

```cpp
#include <memory>

auto p = ______;   // 创建一个持有 int(42) 的 unique_ptr
```

使用推荐的工厂函数（C++14 引入）填写横线。

<!--
答案：std::make_unique<int>(42)
-->

## Explanation

应填写 `std::make_unique<int>(42)`，它会构造值为 42 的 `int` 并返回拥有它的 `std::unique_ptr<int>`。相比 `std::unique_ptr<int>(new int(42))`，工厂函数更简洁，也更不容易在复杂表达式中产生异常安全问题。常见误区是用 `make_shared`，但那会得到共享所有权而非独占所有权。
