---
qid: cpp-algo-deep-031
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码的输出是？

```cpp
std::vector<int> v{1,2,3,4};
std::vector<int> p(4), e(4), i(4);
std::partial_sum (v.begin(), v.end(), p.begin());
std::exclusive_scan(v.begin(), v.end(), e.begin(), 0);  // C++17
std::inclusive_scan(v.begin(), v.end(), i.begin());     // C++17
// p, e, i 分别是？
```

A. p=`1 3 6 10`, e=`1 3 6 10`, i=`0 1 3 6`
B. p=`1 3 6 10`, e=`0 1 3 6`, i=`0 1 3 6`
C. p=`1 3 6 10`, e=`0 1 3 6`, i=`1 3 6 10`
D. 全部相等

## 解析

正确答案是 C：partial_sum 和 inclusive_scan 都包含当前元素，所以结果都是 1 3 6 10。exclusive_scan 不包含当前元素，并从初值 0 开始，因此是 0 1 3 6。误区是把 inclusive 与 exclusive 的边界含义混淆。
