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

## 函数签名
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

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数