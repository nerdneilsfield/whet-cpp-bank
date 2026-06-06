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

## Explanation

从 `(0,0)` 开始 BFS，每个格子第一次入队时记录距离，按四个方向扩展可走且未访问的格子。BFS 按层推进，所以第一次到达终点的距离就是最短步数。边界包括空网格、起点或终点为墙、单格迷宫，以及访问数组要防止重复入队。
