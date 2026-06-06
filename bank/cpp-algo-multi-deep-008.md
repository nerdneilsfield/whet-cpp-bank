---
qid: cpp-algo-multi-deep-008
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: [A, B, D]
---

关于 C++20 ranges 的优势，下列哪些**正确**？（多选）

```cpp
auto r = v | std::views::filter(odd) | std::views::transform(square);
```

A. 视图（views）**惰性求值**，不产生中间容器
B. ranges 算法支持**投影**（projection）参数，可在比较前映射元素
C. ranges 算法不能用于普通迭代器对，只能用于 view
D. 对临时容器调用返回迭代器的算法会得到 `std::ranges::dangling`，把潜在 UB 提前为编译期错误

## Explanation

正确选项是 A、B、D。views 是惰性组合，通常不产生中间容器；ranges 算法还支持 projection，把取键逻辑与比较器分开。ranges 既可接收 range 也可接收迭代器对；对临时 range 返回迭代器时用 dangling 降低悬挂风险。
