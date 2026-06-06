---
qid: cpp-prog-search-rotated-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-search-rotated-001/
---
旋转排序数组（元素互不相同）中查找 `target` 下标，未找到返回 -1。要求 O(log n)。

```cpp
#include <vector>
int searchRotated(const std::vector<int>& a, int target);
```