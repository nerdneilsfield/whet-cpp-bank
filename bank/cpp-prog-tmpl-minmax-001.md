---
qid: cpp-prog-tmpl-minmax-001
type: prog
kp: [cpp-templates]
primary_kp: cpp-templates
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-tmpl-minmax-001/
---
实现可变参数模板 vmin(a, b, ...) 返回所有参数中的最小值（至少 1 个参数）。

### 函数签名
```cpp
// solution.hpp
#pragma once

template <class T>
T vmin(T a);

template <class T, class... Rest>
T vmin(T a, Rest... rest);
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
用单参数重载作为递归基，直接返回唯一参数。多参数版本先递归调用 `vmin(rest...)` 求剩余参数的最小值，再与当前 `a` 比较并返回较小者。注意题目签名返回 `T`，测试通常会传同类型参数；不要写需要空参数包的重载，否则至少一个参数的约束会被破坏。
