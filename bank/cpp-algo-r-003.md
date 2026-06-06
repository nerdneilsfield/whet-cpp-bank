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

正确答案是 A。`std::transform` 的一元版本允许输出区间从输入区间起点开始，因此 `v.begin()` 既作输入又作输出是合法的原地变换。lambda 将每个元素乘以 2，最终 `v` 变为 `2 4 6 8 10`。需要注意的是，输出区间不能以会破坏尚未读取元素的方式部分重叠。
