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