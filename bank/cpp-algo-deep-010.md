---
qid: cpp-algo-deep-010
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码用 `std::reverse_copy` 与 `std::reverse` 哪种更合适？

```cpp
std::vector<int> src{1,2,3,4,5};
std::vector<int> dst;
// 需求：dst 得到反转后的副本，src 保持不变
???
```

A. `std::reverse(src.begin(), src.end()); dst = src;`
B. `dst.assign(src.rbegin(), src.rend()); std::reverse(src.begin(), src.end());`
C. `dst.resize(src.size()); std::reverse_copy(src.begin(), src.end(), dst.begin());`
D. `std::transform(src.rbegin(), src.rend(), std::back_inserter(dst), std::reverse{});`

---

**解析：**

`std::reverse_copy(first, last, dest)` 把 `[first, last)` 反转后写入 `dest`，**不修改源**。要求 `dest` 已有足够空间，或使用 `std::back_inserter(dst)` 配合空容器。

A 修改了 `src`，违反需求；B 工作但多余地再次反转 `src`；D 中 `std::reverse` 不是函数对象，不能当 unary_op。另一种简洁写法：`std::vector<int> dst(src.rbegin(), src.rend());`。
