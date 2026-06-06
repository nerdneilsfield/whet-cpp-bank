---
qid: cpp-taste-algo-003
type: single
kp: [cpp-algorithms, cpp-containers, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: D
tags: [code-taste, best-practice]
---

要去掉 vector<int> 里的重复值，只保留首次出现的唯一元素。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> v;
// ... fill v ...
std::vector<int> result;
for (auto x : v) {
    if (std::count(result.begin(), result.end(), x) == 0) {
        result.push_back(x);
    }
}

// B
std::vector<int> v;
// ... fill v ...
std::set<int> seen(v.begin(), v.end());
std::vector<int> result(seen.begin(), seen.end());

// C
std::vector<int> v;
// ... fill v ...
std::unordered_set<int> seen;
std::vector<int> result;
for (auto x : v) {
    if (seen.insert(x).second) {
        result.push_back(x);
    }
}

// D
std::sort(v.begin(), v.end());
auto it = std::unique(v.begin(), v.end());
v.erase(it, v.end());
```

A. A — count 检查最直白，好懂

B. B — set 构造一句完成，零手写循环

C. C — unordered_set + 插入判断，O(n) 最快

D. D — sort + unique，标准方法

---

**解析：**

选 D。这道题的核心陷阱是："去重"通常意味着**就地压缩**，而 A/B/C 都创建了新容器。

逐一品味为什么其他版本不好：

- **A**：`count` 每次 O(n)，整体 O(n²)。读代码的人要停下来想"count 是什么？哦它在检查是否已存在"。这比直接表达"去重"绕了一个弯。

- **B**：`set` 自动去重没错，但问题有两点：第一，`set` 根据 `operator<` 排序，**结果顺序改变了**——而题目要求"保留首次出现的顺序"！第二，`set` 是红黑树，插入 O(log n)，整体 O(n log n)，内存开销也比 vector 大得多。

- **C**：`unordered_set` + `insert` 返回的 `second`，这其实是 C++ 里"记录首次出现"的经典写法。但它的问题在于：**题目没说不能修改原容器，但此题追求纯粹的"去重"效果，不需要维持原序吗？** 注意题目说"只保留首次出现的唯一元素"——C 保留了首次出现的顺序，但 D 的 sort + unique 不保留原序。如果原序不重要，D 更简单；如果原序重要，C 才是对的。但在 C++ 面试语境里，标准答案普遍倾向 `sort + unique`，因为 `unique` 是专门为"去重"设计的 algorithm，它的名字就是意图。而且 `unordered_set` 版本的代码量显著更大。

D 的 `sort` + `unique` 两句：排序让相同的元素相邻，`unique` 把多余的元素移到尾部，`erase` 截掉。O(n log n)，无额外分配。`unique` 的名字就在说"拿去重"。

核心识别点：
- 不要求保持原序 + 去重 → `sort` + `unique` + `erase`
- 要求保持原序 → `unordered_set` 记录已见（C 的做法是合理的，但可读性不如 D）
- 写 `count(..., x) == 0` 来判重是新手行为