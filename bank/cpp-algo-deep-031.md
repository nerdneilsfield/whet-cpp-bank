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

---

**解析：**

- `partial_sum`：`p[k] = v[0] + ... + v[k]`（包含当前），即 inclusive
- `inclusive_scan`：与 `partial_sum` 同结果（但 C++17 起允许并行且要求关联可重排）
- `exclusive_scan(first, last, dest, init)`：`e[k] = init + v[0] + ... + v[k-1]`（**不含**当前；`e[0] = init`）

两者主要差别是 `inclusive_scan`/`exclusive_scan` 接受 `ExecutionPolicy` 做并行化，要求加法**结合律**；而 `partial_sum` 严格按顺序串行。

GPU/SIMD 常用 exclusive scan 做"前缀偏移表"，第 k 元素正好是前 k 个的总和。
