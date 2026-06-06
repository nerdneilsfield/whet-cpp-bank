---
qid: cpp-taste-algo-008
type: single
kp: [cpp-algorithms, cpp-iterators]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
tags: [code-taste, best-practice]
---

要计算 vector<int> 中相邻元素的差值（d[i] = v[i+1] - v[i]），结果放在新 vector 里。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> v{3, 8, 2, 9, 1};
std::vector<int> d(v.size() - 1);
for (std::size_t i = 0; i + 1 < v.size(); ++i) {
    d[i] = v[i + 1] - v[i];
}

// B
std::vector<int> v{3, 8, 2, 9, 1};
std::vector<int> d;
for (auto it = v.begin() + 1; it != v.end(); ++it) {
    d.push_back(*it - *(it - 1));
}

// C
std::vector<int> v{3, 8, 2, 9, 1};
std::vector<int> d;
std::adjacent_difference(v.begin(), v.end(),
                         std::back_inserter(d));
d.erase(d.begin());  // 第一个元素是 v[0] - 0，不是差值

// D
std::vector<int> v{3, 8, 2, 9, 1};
std::vector<int> d(v.size());
for (std::size_t i = 0; i + 1 < v.size(); ++i) {
    d[i] = v[i + 1] - v[i];
}
std::sort(d.begin(), d.end());
```

A. A — 下标循环最直接

B. B — 迭代器写法，避开下标

C. C — adjacent_difference 名字就是"相邻差值"

D. D — 顺便 sort 一下，一步顶两步

---

**解析：**

选 C。`std::adjacent_difference` 是标准库中专做"相邻差值"的 algorithm，名字明确，语义清晰。

逐一品味为什么其他版本不好：

- **A**：下标循环。`v[i+1] - v[i]` 看起来明确，但你还是得自己管边界条件 `i + 1 < v.size()`。读者看完整段才知道这是在算相邻差值。如果循环体内再混入其他逻辑，意图就更模糊了。

- **B**：迭代器版本更现代一点，但 `*(it - 1)` 的反向引用不够直观。每一步都在用过去的元素做减法——这在 mental model 上比正向下标更绕。

- **D**：**致命问题**——你根本**不知道 D 在提交什么**。`adjacent_difference` 是确定性的 O(n)，D 里强行加了个 `sort`。如果是手误写的，这是 bug；如果是故意的，这是"隐藏的排序"。不管哪种情况，结果都不对——排序后差值对的顺序全乱了（虽然本题里没提需要保持顺序，但差值的自然定义要求位置对应）。这题 D 是在混淆视听。

C 是唯一一个名字直接对应"相邻元素差值"的写法。`adjacent_difference` 的第一个输出元素是 `v[0] - 0`（严格说是 `v[0] - T{}`），所以需要 `erase` 掉第一个。这是已知的 API 设计瑕疵，但瑕不掩瑜——名字就是意图声明。

核心识别点：
- 相邻元素运算 → `adjacent_difference`（差值），`adjacent_find`（查找）
- 部分和 → `partial_sum`
- 内部乘积 → `inner_product`
- 这些都是 `<numeric>` 里的数值 algorithm

## Explanation

正确答案是 C。`std::adjacent_difference` 是标准库中专做"相邻差值"的 algorithm，名字明确，语义清晰。
B：迭代器版本更现代一点，但 `*(it - 1)` 的反向引用不够直观。
常见误区是手写循环或只看单步结果，忽略标准算法已经约定好的复杂度和迭代器语义。
