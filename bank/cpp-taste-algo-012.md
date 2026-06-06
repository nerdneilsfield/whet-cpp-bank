---
qid: cpp-taste-algo-012
type: single
kp: [cpp-algorithms, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: D
tags: [code-taste, best-practice]
---

检查 vector<int> 中是否有重复值。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
bool has_dup(const std::vector<int>& v) {
    for (std::size_t i = 0; i < v.size(); ++i) {
        for (std::size_t j = i + 1; j < v.size(); ++j) {
            if (v[i] == v[j]) return true;
        }
    }
    return false;
}

// B
bool has_dup(const std::vector<int>& v) {
    std::unordered_set<int> seen;
    for (auto x : v) {
        if (seen.count(x)) return true;
        seen.insert(x);
    }
    return false;
}

// C
bool has_dup(const std::vector<int>& v) {
    for (auto x : v) {
        if (std::count(v.begin(), v.end(), x) > 1) return true;
    }
    return false;
}

// D
bool has_dup(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    return std::adjacent_find(v.begin(), v.end()) != v.end();
}
```

A. A — 两层循环，不修改原容器

B. B — 哈希表记录已见，O(n) 高效

C. C — count > 1 就返回，直观

D. D — 拷贝 + sort + adjacent_find，标准写法

---

**解析：**

选 D。这是 C++ 面试经典题，`adjacent_find` 的语义是"找到第一对相邻的相等元素"——正是"检查重复"需要的。

逐一品味为什么其他版本不好：

- **A**：两层循环 O(n²)。1000 个元素就需要 50 万次比较。在面试题里写两层循环查重复，基本上是在告诉面试官："我没看过 STL algorithm 库"。

- **B**：`unordered_set` + `count` 在多数情况下是最优解——O(n) 期望时间，不修改原容器。但这里有个细节：**先 `count` 再 `insert` 是做了两次哈希操作**。实际上 C++ 的 `insert` 返回值已经包含了是否插入成功的信息（`seen.insert(x).second`），不需要先 `count` 再 `insert`。而且 `unordered_set` 有额外的内存开销（哈希表）。

- **C**：对每个元素都 `count` 一遍整个范围。每个 `count` 是 O(n)，n 个元素就是 O(n²)，和 A 一样差，只是包装得更漂亮了。

D 的做法：拷贝（如果允许修改则不需要）→ sort → adjaccent_find。排序让相等的元素相邻，`adjacent_find` 检查相邻元素是否相等。O(n log n)，零额外分配（除了排序可能的临时空间）。

核心识别点：
- "相邻相等" → `adjacent_find`
- "去重" → `unique`（需要 sort 前置）
- "判重" → `sort` + `adjacent_find` 或 `unordered_set` + 插入判断
- 不要用 `count()` 判重——那会让你每次都扫全量
- `adjacent_find` 这个名字本身就在说"找相邻的相等"