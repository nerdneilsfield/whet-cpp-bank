---
qid: cpp-prog-ds-queue-bfs-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-ds-queue-bfs-001/
---
用 BFS（`std::queue`）求 4-连通迷宫从 `(0,0)` 到 `(R-1,C-1)` 的最短步数。`grid[i][j]==0` 可走、`1` 是墙。起点/终点也必须是 0；无解返回 -1。返回值为经过格子数（含起点）减 1，即步数；若起点等终点返回 0。

```cpp
#include <vector>
int shortestPath(const std::vector<std::vector<int>>& grid);
```