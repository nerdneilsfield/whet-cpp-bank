---
qid: cpp-cross-la-003
type: fill
kp: [cpp-lambdas, cpp-algorithms]
difficulty: easy
answer_key: "3"
---

以下代码的输出结果是什么？（填写输出的整数值）

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {2, 5, 8, 3, 6, 1, 7};
    int cnt = std::count_if(v.begin(), v.end(), [](int x) {
        return x > 5;
    });
    std::cout << cnt << std::endl;
    return 0;
}
```

<!--
逐元素检查：2(否)、5(否)、8(是)、3(否)、6(是)、1(否)、7(是) → 共 3 个元素大于 5，cnt = 3。
-->

## 解析

答案是 `3`。`std::count_if` 对每个元素应用 lambda，只统计严格大于 5 的元素。序列中满足条件的是 8、6、7，共三个；5 本身不满足，因为条件不是大于等于。关键误区是把 `> 5` 看成 `>= 5`，或把 count_if 当成求和。
