---
qid: cpp-algo-r-003
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: "A"
---

## 题目

以下代码能否正确编译并运行，输出是什么？

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::transform(v.begin(), v.end(), v.begin(), [](int x){ return x * 2; });
    for (int x : v) std::cout << x << " ";
}
```

A. `2 4 6 8 10`
B. 未定义行为，输入输出范围重叠不允许
C. 编译错误
D. `1 2 3 4 5`（原地变换无效）

## 解析

`std::transform` 的输出迭代器允许与输入范围完全重叠（即原地变换），这是标准合法用法。结果将每个元素乘以 2，输出 `2 4 6 8 10`。注意：与某些算法不同，`transform` 不要求输入输出范围不重叠。
