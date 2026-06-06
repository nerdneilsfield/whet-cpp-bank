---
qid: cpp-cross-me-004
type: single
kp: [cpp-memory-mgmt, cpp-exceptions]
difficulty: easy
answer_key: B
---

# 题目

```cpp
#include <memory>
#include <stdexcept>

noexcept void setup() noexcept {
    auto p = std::make_unique<int[]>(1024 * 1024 * 1024); // 4 GB
    // ... 使用 p
}
```

关于此代码，下列说法**正确**的是？

A. 函数标记 `noexcept`，因此分配失败时程序静默跳过，不会有任何问题

B. 若分配失败，`make_unique` 抛出 `std::bad_alloc`；因函数是 `noexcept`，C++ 运行时会调用 `std::terminate()` 终止程序

C. `make_unique` 在 `noexcept` 函数中被隐式替换为 `new(std::nothrow)`，返回 `nullptr`

D. 编译器会拒绝编译：`noexcept` 函数内不允许调用可能抛异常的表达式

---

## Explanation

- `make_unique` 底层调用 `new`，可以抛出 `std::bad_alloc`，这与函数签名中的 `noexcept` **无关**——编译器不会禁止此组合，也不会静默替换。
- 若异常确实从 `noexcept` 函数中传播出去，C++ 标准规定运行时直接调用 `std::terminate()`，程序终止。
- 选 **B**。

> **实践建议：** 若确实需要 `noexcept` 保证，在分配前先用 `new(std::nothrow)` 或包一层 `try/catch` 处理 `bad_alloc`，而不是依赖运行时终止。
