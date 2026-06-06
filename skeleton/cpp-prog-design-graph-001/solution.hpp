#pragma once
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>

class Graph {
    std::unordered_map<int, std::unordered_set<int>> adj_;
public:
    void add_edge(int u, int v) { adj_[u].insert(v); adj_[v]; }
    bool has_edge(int u, int v) const {
        auto it = adj_.find(u);
        return it != adj_.end() && it->second.count(v);
    }
    bool has_path(int u, int v) const {
        if (u == v) return true;
        std::queue<int> q;
        std::unordered_set<int> visited;
        q.push(u);
        visited.insert(u);
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            auto it = adj_.find(cur);
            if (it == adj_.end()) continue;
            for (int nb : it->second) {
                if (nb == v) return true;
                if (visited.insert(nb).second) q.push(nb);
            }
        }
        return false;
    }
    std::size_t vertex_count() const { return adj_.size(); }
};
