---
qid: cpp-taste-algo-017
type: single
kp: [cpp-containers, cpp-stl-basics]
primary_kp: cpp-containers
difficulty: medium
answer_key: C
tags: [code-taste, best-practice]
---

要检查 `std::map<int, std::string>` 中是否存在某个 key。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
bool exists = false;
for (const auto& [k, v] : m) {
    if (k == 2) { exists = true; break; }
}

// B
std::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
bool exists = m[2] != std::string{};  // or !m[2].empty()

// C
std::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
bool exists = m.find(2) != m.end();

// D
std::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
bool exists = m.count(2) > 0;
```

A. A — 遍历 map 找 key，不使用 map 的搜索能力

B. B — operator[]，最简洁

C. C — find，标准关联容器查找方式

D. D — count，一行搞定

---

**解析：**

选 C。`map::find` 是关联容器查找的标准方法——"找到了吗？指向有效元素的迭代器就是找到了。"

逐一品味为什么其他版本不好：

- **A**：遍历整个 map 来找 key——这是对 `std::map` 红黑树 O(log n) 查找能力的无视。100 万个元素时，`find` 平均做 20 次比较；遍历平均做 50 万次。

- **B**：`operator[]` 会**插入一个默认构造的值**如果 key 不存在。检查 `m[2] != std::string{}` 时，如果 key 2 不存在，这一行代码**往 map 里插入了 `{2, ""}`**——副作用巨大。函数签名如果是 const map& 甚至编译不过。这是经典的 bug origin。

- **D**：`count` 能工作，返回匹配 key 的数量（对 map 只能是 0 或 1）。C++20 之前很多人用 `count` 而不是 `find` 判存在，但 `count` 的语义是"计数"，不是"查找"。`count` 可能比 `find` 做得更多吗？标准不要求，但 `count` 在某些实现里可能遍历重复 key（multimap 场景），对普通 map 也是 O(log n)。**更关键的是意图**：`count` 说"我想知道有多少个"；`find` 说"我想找到它"。

`find` 返回的迭代器可以**直接访问 value**（`it->second`），而 `count` 只告诉你"在不在"。如果后续需要取出值，用 `count` 判存在再 `operator[]` 取值是两次 O(log n) 操作；`find` 一次搞定。

核心识别点：
- 检查存在 + 可能取值 → `find`
- 仅检查存在 → `find` 仍首选取代 `count`（意图更清楚）
- `operator[]` 对存在检查是**有害的**——它会在不存在时插入
- C++20 有 `contains()` 成员函数，只检查存在性更直接