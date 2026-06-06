---
qid: cpp-iter-r-003
type: single
kp: [cpp-iterators]
difficulty: easy
answer_key: "A"
---

## 题目

阅读以下代码，`*it` 和 `*it2` 的值分别是什么？

```cpp
#include <vector>
#include <iterator>
#include <iostream>

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};
    auto it = v.begin();
    auto it2 = std::next(it, 3);
    std::cout << *it << " " << *it2 << std::endl;
}
```

A. `10 40`
B. `40 40`
C. `10 30`
D. `40 10`

## 解析

`std::next(it, n)` 返回一个**新迭代器**，指向从 `it` 起前进 `n` 步的位置，**不修改 `it` 本身**。因此 `it` 仍指向 `v[0]`（值 `10`），`it2` 指向 `v[3]`（值 `40`），输出 `10 40`。这与 `std::advance` 的就地修改语义相反，是重要区别。
