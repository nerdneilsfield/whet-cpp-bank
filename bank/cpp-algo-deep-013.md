---
qid: cpp-algo-deep-013
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

统计 `v` 中正数的个数，下列哪种写法**最直接**且语义最清晰？

```cpp
std::vector<int> v{-2, 1, 3, -4, 5, 6};
???
```

A. `std::accumulate(v.begin(), v.end(), 0);`
B. `std::count_if(v.begin(), v.end(), [](int x){return x > 0;});`
C. `std::accumulate(v.begin(), v.end(), 0, [](int s, int x){return x > 0 ? s+x : s;});`
D. `std::find_if(v.begin(), v.end(), [](int x){return x > 0;}) - v.begin();`

---

**解析：**

`count_if` 直接返回满足谓词的元素**个数**，复杂度 O(n)，语义最清晰，返回类型 `iterator::difference_type`。

A 求的是元素之和，不是个数；C 用 accumulate 做计数可行但语义不直接，且若改成 `s+1` 才是计数；D 只能找到第一个满足者的位置，不是总数。选择算法时应优先匹配语义。
