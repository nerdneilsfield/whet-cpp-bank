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

## Explanation

二分时至少有一半区间是有序的，先判断左半 `[l, mid]` 还是右半 `[mid, r]` 有序，再判断 target 是否落在有序半区内来收缩边界。元素互不相同使有序半区判断没有歧义。注意空数组返回 -1，边界更新要避免死循环。
