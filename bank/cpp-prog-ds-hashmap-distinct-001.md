---
qid: cpp-prog-ds-hashmap-distinct-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-ds-hashmap-distinct-001/
---
用 `std::unordered_set` 统计数组中不同元素的个数。

```cpp
#include <vector>
int countDistinct(const std::vector<int>& a);
```

## Explanation

把数组元素逐个插入 `std::unordered_set<int>`，最后集合大小就是不同元素个数。哈希集合自动去重，平均复杂度为 O(n)。注意不要用排序改变复杂度要求，也不要把重复元素重复计数。
