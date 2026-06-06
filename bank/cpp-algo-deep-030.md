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

---

**解析：**

`std::inner_product(f1, l1, f2, init)` 默认计算 `init + Σ (a[i] * b[i])`，正是点积。可重载传入自定义"加"与"乘"做更一般的归约：

```cpp
// 等价于 sum of (a[i] - b[i])^2 累加成 平方误差
std::inner_product(a.begin(), a.end(), b.begin(), 0,
    std::plus<>{},
    [](int x, int y){ int d = x - y; return d*d; });
```

`std::reduce` 不接受两个序列；要并行点积可用 `std::transform_reduce`（C++17）：

```cpp
std::transform_reduce(std::execution::par, a.begin(), a.end(), b.begin(), 0);
```
