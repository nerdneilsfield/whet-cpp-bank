---
qid: cpp-algo-deep-016
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码 `std::mismatch` 的返回类型是？

```cpp
std::vector<int> a{1, 2, 3, 4};
std::vector<int> b{1, 2, 9, 4};
auto r = std::mismatch(a.begin(), a.end(), b.begin());
// 输出 r 的相关信息
```

A. `int`，等于第一个不匹配位置的下标
B. `bool`，是否完全相等
C. `std::pair<iterator, iterator>`，分别指向两序列第一次不相等处
D. `std::vector<int>`，所有不匹配的元素

---

**解析：**

`std::mismatch` 返回 `std::pair<It1, It2>`：

- `r.first` 指向第一序列第一处不匹配
- `r.second` 指向第二序列对应位置

本例 `r.first` 指 `a[2] (=3)`，`r.second` 指 `b[2] (=9)`。若全相等，两个迭代器分别等于 `last1` 和 `b.begin()+(last1-first1)`。

同样有三参数与四参数版本的对称问题，C++14 起推荐四参数版避免越界。
