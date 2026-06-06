---
qid: cpp-algo-deep-024
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: D
---

下列代码用 `std::lexicographical_compare` 比较两个数组，结果是？

```cpp
std::vector<int> a{1, 2, 3};
std::vector<int> b{1, 2, 3, 0};
bool less = std::lexicographical_compare(
    a.begin(), a.end(), b.begin(), b.end());
std::cout << less;
```

A. `0`（false，因为前缀相同）
B. `0`，因为 `a` 短的反而"大"
C. `1`，因为元素和小
D. `1`，前缀相同时**短的字典序更小**

## Explanation

正确答案是 D：字典序比较先找第一处不同，若没有不同且一方先结束，则较短者更小。a 是 b 的完全前缀且更短，所以 a < b，返回 true，也就是输出 1。误区是按元素和或长度单独比较；字典序只看首个差异和前缀关系，这与字符串排序规则相同。
