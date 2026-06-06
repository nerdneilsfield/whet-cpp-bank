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

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

void rotate_left(std::vector<int>& v, int k);
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
先处理空数组，否则对 `k` 取模得到真实左移步数。可以直接调用 `std::rotate(v.begin(), v.begin() + k, v.end())`，也可以三次反转实现原地旋转。`k == 0` 或 `k` 是长度倍数时不应改变数组。
