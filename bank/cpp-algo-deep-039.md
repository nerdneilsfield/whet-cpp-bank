---
qid: cpp-algo-deep-039
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码用 `std::includes` 判断 `a ⊇ b`，结果是？

```cpp
std::vector<int> a{1,2,3,4,5,6};
std::vector<int> b{2,4,6};
bool r = std::includes(a.begin(), a.end(), b.begin(), b.end());
std::cout << r;
```

A. `0`，因为 `b` 不是 `a` 的连续子序列
B. `1`，因为元素之和相同
C. `1`，`a` 包含 `b` 的所有元素（按有序集合包含语义，要求两端都已排序）
D. UB，需要 `std::set`

---

**解析：**

`std::includes(f1,l1,f2,l2)` 判断 `[f2,l2)` 是否是 `[f1,l1)` 的**子集**（按多重集合语义）：要求两序列都已按同一比较器排序，复杂度 O(m+n)。

不是"子串"或"连续子序列"——所以不要求 `b` 的元素连续出现在 `a` 中；只要 `a` 含有 `b` 每个元素至少同样多次。

对未排序序列**结果未定义**。若需要无序判断，用 `std::set` / `std::unordered_set` 或先 sort 再 includes。
