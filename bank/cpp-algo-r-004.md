---
qid: cpp-algo-r-004
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: "D"
---

### 题目

以下代码输出什么？

```cpp
#include <vector>
<algorithm>
#include <iostream>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
    bool found = std::binary_search(v.begin(), v.end(), 4);
    std::cout << (found ? "found" : "not found") << std::endl;
}
```

A. `found`
B. `not found`
C. 编译错误（缺少 `#include`）
D. 未定义行为，结果不可靠

## Explanation

`std::binary_search` 要求范围必须已排序（或至少满足分区条件），否则行为未定义。本题 `v` 未排序，因此结果不可靠。代码也有 `#include` 拼写错误（`<algorithm>` 缺少 `#include`），会导致编译错误；但即使修复后，对未排序序列调用 `binary_search` 仍是未定义行为。
