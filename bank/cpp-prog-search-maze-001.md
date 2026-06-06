---
qid: cpp-prog-search-maze-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-search-maze-001/
---
DFS 判断 4-连通迷宫中从 `(sr,sc)` 是否能到 `(tr,tc)`。`grid[i][j]==0` 可走、`1` 是墙。起终点若是 `1` 视为不可达，返回 false。

```cpp
#include <vector>
bool hasPath(std::vector<std::vector<int>> grid, int sr, int sc, int tr, int tc);
```