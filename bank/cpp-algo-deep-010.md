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

## 解析

正确答案是 C：std::reverse_copy 会把源区间反向复制到目标区间，不修改 src，符合“副本反转、源不变”的需求。A 修改了 src，B 又额外反转 src，D 把 reverse 当函数对象使用也不成立。注意目标迭代器必须有足够空间，或改用 back_inserter。
