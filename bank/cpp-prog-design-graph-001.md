---
qid: cpp-prog-design-graph-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-design-graph-001/
---
实现有向图（邻接表）。支持 add_edge(u,v)、has_edge(u,v)、has_path(u,v) BFS 判通。

### 函数签名
```cpp
#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Graph {
public:
    void add_edge(int u, int v);
    bool has_edge(int u, int v) const;
    bool has_path(int u, int v) const;
    std::size_t vertex_count() const;
private:
    std::unordered_map<int, std::unordered_set<int>> adj_;
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

邻接表用 `unordered_map<int, unordered_set<int>>` 存边，`add_edge` 插入 `v` 到 `u` 的邻接集合，并确保孤立目标点也能计入顶点数。`has_edge` 只检查直接邻接，`has_path` 用队列 BFS 和 visited 集合避免重复访问与环。边界上 `u == v` 可视为存在长度为 0 的路径，但顶点是否已在图中要按测试约定处理。
