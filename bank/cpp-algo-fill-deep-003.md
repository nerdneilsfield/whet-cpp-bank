---
qid: cpp-algo-fill-deep-003
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["<numeric>", "numeric"]
---

`std::accumulate`、`std::inner_product`、`std::partial_sum`、`std::iota`、`std::reduce`、`std::gcd`、`std::lcm`、`std::midpoint` 这些算法都定义在头文件 _______ 中。

---

**解析：**

`<numeric>` 头文件专门容纳数值型算法（不在 `<algorithm>`）：

| 算法 | C++ 版本 |
|---|---|
| `accumulate` / `inner_product` / `partial_sum` / `adjacent_difference` / `iota` | C++98 / iota C++11 |
| `reduce` / `inclusive_scan` / `exclusive_scan` / `transform_reduce` / `transform_inclusive_scan` / `transform_exclusive_scan` | C++17 |
| `gcd` / `lcm` | C++17 |
| `midpoint` | C++20 |

并行版本（接受 `std::execution::par`）也在 `<numeric>`。常见错误：忘记 include `<numeric>` 只 include `<algorithm>` 编译报错。
