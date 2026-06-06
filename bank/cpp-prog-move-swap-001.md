---
qid: cpp-prog-move-swap-001
type: prog
kp: [cpp-move-semantics]
primary_kp: cpp-move-semantics
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-move-swap-001/
---
实现泛型 my_swap(a, b)：使用移动语义交换两个对象。要求 noexcept-friendly（不强制声明）。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <utility>

template <class T>
void my_swap(T& a, T& b);
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
交换过程应避免拷贝：先用 `T tmp = std::move(a)` 保存左值资源，再把 `b` 移给 `a`，最后把 `tmp` 移给 `b`。这样对 move-only 类型也能工作。若声明 `noexcept`，可以基于 `std::is_nothrow_move_constructible` 和 `std::is_nothrow_move_assignable`，但题目不强制。
