---
qid: cpp-algo-deep-008
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码用 `std::transform` 计算两个向量逐元素之和，正确写法是？

```cpp
std::vector<int> a{1,2,3}, b{10,20,30}, c(3);
???
// 期望 c = {11, 22, 33}
```

A. `std::transform(a.begin(), a.end(), c.begin(), [&](int x){return x + b[&x - &a[0]];});`
B. `std::transform(a.begin(), a.end(), c.begin(), std::plus<int>{});`
C. `std::transform(a.begin(), a.end(), b.begin(), c.begin(), std::plus<int>{});`
D. `std::transform(a.begin(), a.end(), b.begin(), b.end(), c.begin(), std::plus<int>{});`

## Explanation

正确答案是 C：二元版本 std::transform 的形态是 first1, last1, first2, dest, binary_op，第二个输入序列只给起始迭代器。B 使用了一元版本却传二元加法器，D 多传了 b.end()，都不符合签名。A 试图从引用地址推下标，既脆弱也不必要。
