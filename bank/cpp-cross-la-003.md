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
