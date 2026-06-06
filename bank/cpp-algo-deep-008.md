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

---

**解析：**

`std::transform` 有两种形态：

```cpp
// unary: 单输入
transform(first1, last1, dest, unary_op);
// binary: 双输入（第二序列只传 begin，长度由第一序列决定）
transform(first1, last1, first2, dest, binary_op);
```

D 选项多写了 `b.end()`，编译错误；A 用迭代器算术绕过去的写法极易越界且依赖元素相邻；B 把 binary_op 当成 unary_op 使用，编译错误。
