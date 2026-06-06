---
qid: cpp-algo-deep-030
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码计算两个向量的点积，正确写法是？

```cpp
std::vector<int> a{1,2,3};
std::vector<int> b{4,5,6};
???
// 期望 1*4 + 2*5 + 3*6 = 32
```

A. `std::accumulate(a.begin(), a.end(), 0, std::multiplies<int>{});`
B. `std::transform(a.begin(), a.end(), b.begin(), std::multiplies<int>{});`
C. `std::inner_product(a.begin(), a.end(), b.begin(), 0);`
D. `std::reduce(a.begin(), a.end(), b.begin(), 0);`

## Explanation

正确答案是 C：std::inner_product 默认计算 init 加上两序列逐元素乘积之和，正是点积。accumulate 只处理一个序列，transform 只生成输出不做求和。若需要并行或先变换再归约，可考虑 transform_reduce。
