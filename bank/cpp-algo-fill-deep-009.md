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

---

**解析：**

`std::views::transform`（或 `std::ranges::views::transform`）：对底层 range 的每个元素应用一元函数，返回一个**惰性视图**：

```cpp
auto sq = v | std::views::transform([](int x){ return x*x; });
for (int y : sq) std::cout << y << " ";  // 元素按需计算
```

特性：
- 零分配（无中间容器）
- 元素类型 = 函数返回类型
- 迭代器类别 ≤ 底层迭代器类别

可与其它 view 链式组合，如 `views::filter`、`views::take`、`views::drop`、`views::reverse` 等。C++23 起可用 `std::ranges::to<std::vector>()` 物化。
