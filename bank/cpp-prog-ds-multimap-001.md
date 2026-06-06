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