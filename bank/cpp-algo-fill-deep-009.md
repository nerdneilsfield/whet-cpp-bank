---
qid: cpp-algo-fill-deep-009
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["std::views::transform", "views::transform", "std::ranges::views::transform"]
---

下列 C++20 代码把每个元素映射为其平方：

```cpp
auto sq = v | _______([](int x){ return x * x; });
```

请补全所用 view 适配器（含命名空间）。

## Explanation

答案是 std::views::transform。它是 C++20 ranges 的 view 适配器，返回惰性视图，只有遍历结果时才对元素应用平方函数，不会立刻生成新容器。误区是把 views 管道当作 eager 计算；若需要 vector 等容器，还需要额外物化。
