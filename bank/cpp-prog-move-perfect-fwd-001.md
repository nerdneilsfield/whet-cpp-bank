---
qid: cpp-prog-move-perfect-fwd-001
type: prog
kp: [cpp-move-semantics]
primary_kp: cpp-move-semantics
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-move-perfect-fwd-001/
---
实现 wrapper(Func&& f, Args&&... args) 完美转发参数到 f。返回值和异常传递。测试时验证左值/右值/const 引用分类被保留。

## 函数签名
```cpp
#pragma once
#include <utility>

template <typename Func, typename... Args>
decltype(auto) wrapper(Func&& f, Args&&... args);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数