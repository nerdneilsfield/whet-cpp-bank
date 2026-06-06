---
qid: cpp-algo-001
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: C
---

`std::sort` 定义在哪个头文件中？

A. `<numeric>`
B. `<vector>`
C. `<algorithm>`
D. `<iterator>`

## 解析

正确答案是 C。`std::sort` 属于标准库算法组件，声明在 `<algorithm>` 中；使用前应 `#include <algorithm>`。`<numeric>` 主要提供 `std::accumulate`、`std::iota` 等数值算法，`<vector>` 定义容器，`<iterator>` 定义迭代器工具。
