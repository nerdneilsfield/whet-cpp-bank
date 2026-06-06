---
qid: cpp-prog-stl-rotate-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-rotate-001/
---
将数组向左旋转 k 步（k 可大于 size 或为 0）。原地修改。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

void rotate_left(std::vector<int>& v, int k);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数