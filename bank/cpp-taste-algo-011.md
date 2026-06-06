---
qid: cpp-taste-algo-011
type: single
kp: [cpp-algorithms, cpp-iterators, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
tags: [code-taste, best-practice]
---

要在 vector<int> 中**最后一次**找到值 5 的位置。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> v{3, 5, 1, 5, 2, 5, 9};
int last_pos = -1;
for (std::size_t i = 0; i < v.size(); ++i) {
    if (v[i] == 5) last_pos = (int)i;
}

// B
std::vector<int> v{3, 5, 1, 5, 2, 5, 9};
auto it = std::find_end(v.begin(), v.end(),
                        std::vector<int>{5}.begin(),
                        std::vector<int>{5}.end());

// C
std::vector<int> v{3, 5, 1, 5, 2, 5, 9};
auto it = std::find(v.rbegin(), v.rend(), 5);
ptrdiff_t last_pos = std::distance(v.begin(), it.base()) - 1;

// D
std::vector<int> v{3, 5, 1, 5, 2, 5, 9};
std::reverse(v.begin(), v.end());
auto it = std::find(v.begin(), v.end(), 5);
std::reverse(v.begin(), v.end());
ptrdiff_t last_pos = std::distance(v.begin(), it.base());
```

A. A — 逆序遍历手动记录，最快

B. B — find_end 设计用于子串匹配，正好是"最后一次出现"

C. C — 用反向迭代器 rbegin/rend + find，语义就是"从后往前找"

D. D — reverse 两次 + find，保序

---

**解析：**

选 C。反向迭代器 + `find` 是"找最后一次出现"的标准表达。名字 `rbegin()` / `rend()` 告诉读者："从尾到头搜索"。

逐一品味为什么其他版本不好：

- **A**：从头到尾遍历完整个容器，即使目标在靠近尾部的位置也一样。而且引入了 mutating 的 `last_pos` 变量和每次迭代的更新——本质上是"用遍历覆盖了所有位置，最后留下最后一个"，而不是"从后往前找第一个"。

- **B**：`find_end` 本来的语义是"在范围中查找子序列最后一次出现的位置"。用单元素子序列 `{5}` 来搜索，是**对 algorithm 的误用**。名字 "find_end" 在标准里的定义是"在一个范围中查找最后一个匹配某个子序列的位置"——不是"查找最后一个等于某值的元素"。虽然这次碰巧结果正确，但会误导读者以为你在搜索子序列。

- **D**：`reverse` 两次修改了原容器。`std::reverse` 是 in-place 操作，改变了 v 的元素顺序。如果 v 是 const 的或后续代码依赖原序就完了。即使最后 reverse 回来了，**中间状态有副作用**，且两遍 reverse 是 O(n) 的浪费。

核心识别点：
- "第一次出现" → `find`（正向迭代器）
- "最后一次出现" → `find` + reverse iterator（`rbegin` / `rend`）
- 不要用 `find_end` 做单元素搜索——那是子串匹配，语义不对
- 不要为了找最后一个而 reverse 容器
- 反向迭代器是只读的、零开销的抽象