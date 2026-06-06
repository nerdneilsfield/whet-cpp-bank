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

## 函数签名
```cpp
// solution.hpp
#pragma once

template <class T>
T vmin(T a);

template <class T, class... Rest>
T vmin(T a, Rest... rest);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数