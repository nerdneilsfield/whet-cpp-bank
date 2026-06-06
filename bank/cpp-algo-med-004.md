---
qid: cpp-algo-med-004
type: single
kp: [cpp-algorithms]
difficulty: medium
answer_key: C
---

下列代码中 `counter` 最终的值是？

```cpp
std::vector<int> src = {1, 2, 3, 4, 5};
std::vector<int> dst(5);
int counter = 0;
std::transform(src.begin(), src.end(), dst.begin(),
               [&counter](int x) {
                   return x * (++counter);  // 副作用！
               });
```

A. 一定是 `15`，因为 `counter` 自增 5 次
B. 一定是 `5`，对应每个元素被处理一次
C. 是 `5`（被调用 5 次），但 `dst` 中元素与 `counter` 的对应关系**未指定**：标准只保证 lambda 被调用 `last-first` 次，**未规定调用顺序**
D. 行为未定义，因为 `std::transform` 不允许有副作用

---

**解析：**

`std::transform` 的标准规定：对输入区间 `[first1, last1)` 的每个元素调用一次一元函数（或对两个输入区间各取一对调用二元函数），共 `last1 - first1` 次。所以 `counter` 一定是 5。

但标准**没有规定**调用顺序：实现可以从前往后、从后往前，C++17 起还可以传 `std::execution::par` 让多线程并行调。这意味着含可变状态的 lambda 与某个具体输入元素之间的映射关系**未指定**——`dst[0]` 不一定等于 `1*1`，可能等于 `1*3` 或别的乘数。

这条规则的根本动机是给实现优化空间（SIMD、并行、向量化、循环展开）。要安全使用带副作用的变换，要么换用 `std::accumulate`（保证顺序）、`for` 循环显式遍历，要么用 `std::transform` 配合 `std::iota`/索引让映射关系自包含。

D 不对：标准并不"禁止"副作用，只是不保证顺序。同类规则也适用于 `std::for_each`（C++17 起的并行版本不保证顺序，串行重载仍按顺序）、`std::generate`、`std::accumulate` 的并行版本 `std::reduce`。
