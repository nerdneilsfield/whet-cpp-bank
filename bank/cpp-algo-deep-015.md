---
qid: cpp-algo-deep-015
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

下列代码（C++17 及之前）的行为是？

```cpp
std::vector<int> a{1,2,3};
std::vector<int> b{1,2,3,4,5};
bool eq = std::equal(a.begin(), a.end(), b.begin());
```

A. 安全：返回 `false`，因为长度不同
B. 只比较 `a.size()` 个元素，返回 `true`；若 `b` 比 `a` 短则**未定义行为**（越界读 b）
C. 编译错误
D. 总是返回 `true` 仅当两个 vector 完全相等

---

**解析：**

三参数版 `std::equal(first1, last1, first2)` 假设第二序列**至少与第一序列一样长**，不检查；如果 `b` 比 `a` 短，会越界读，UB。

C++14 起新增四参数版 `std::equal(first1, last1, first2, last2)`，会同时检查两端，若长度不同直接返回 `false`，**安全且推荐**。C++20 `ranges::equal(a, b)` 更简洁。

教训：能用四参数版/ranges 版就别用三参数版。
