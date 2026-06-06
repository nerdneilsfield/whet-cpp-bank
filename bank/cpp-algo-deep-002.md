---
qid: cpp-algo-deep-002
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

下列代码意图去重，实际输出是？

```cpp
std::vector<int> v{1, 2, 1, 3, 2, 1, 4};
v.erase(std::unique(v.begin(), v.end()), v.end());
for (auto x : v) std::cout << x << " ";
```

A. `1 2 3 4`
B. `1 2 1 3 2 1 4`
C. `1 2 3 2 1 4`
D. 未定义行为

## 解析

正确答案是 B：std::unique 只消除相邻重复元素，而题中没有相邻相等元素，所以序列保持原样。它不是全局去重算法，也同样只返回逻辑末尾。若要得到 1 2 3 4，通常先 sort 再 unique+erase，或使用 set/unordered_set。
