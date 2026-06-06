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

## Explanation

用 DFS 从起点出发，越界、墙和已访问格子都直接返回 false，到达目标返回 true。每次访问可走格子后标记已访问，再递归搜索四个方向。注意题目按值传入 grid，可以直接修改它作为 visited；起点或终点为墙时应立即失败。
