---
qid: cpp-prog-ds-multimap-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-ds-multimap-001/
---
使用 `std::multimap<std::string,int>` 按键聚合：给定 pairs，返回 `std::map<std::string, std::vector<int>>`，每个 key 对应所有 value，按插入顺序保留。

```cpp
#include <map>
#include <string>
#include <vector>
std::map<std::string, std::vector<int>> groupBy(const std::vector<std::pair<std::string,int>>& pairs);
```

## Explanation

可以先把所有 pair 插入 `std::multimap`，再按 `equal_range` 或顺序遍历把同一 key 的 value 收集到 `std::map<string, vector<int>>`。由于 multimap 按 key 有序，结果 map 也天然按 key 排序。注意题目要求每个 key 内按插入顺序保留，不能对 value 再排序。
