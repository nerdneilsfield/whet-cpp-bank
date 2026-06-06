---
qid: cpp-prog-stl-partition-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-partition-001/
---
实现一次快排 partition：以最后一个元素为 pivot，重排数组使左侧 <= pivot，右侧 > pivot，返回 pivot 的最终下标。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

int partition_last(std::vector<int>& v);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## 解析
使用 Lomuto partition：最后一个元素作为 pivot，维护 `i` 指向下一个 `<= pivot` 的位置。遍历前 `n-1` 个元素，遇到 `<= pivot` 就与 `v[i]` 交换并递增 `i`，最后把 pivot 与 `v[i]` 交换。返回 `i`，要注意空数组若测试涉及应有明确处理，通常可返回 `-1`。
