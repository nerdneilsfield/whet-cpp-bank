---
qid: cpp-cross-la-004
type: single
kp: [cpp-lambdas, cpp-algorithms]
difficulty: easy
answer_key: D
---

以下代码输出是什么？

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dst(5);
    std::transform(src.begin(), src.end(), dst.begin(), [](int x) {
        return x * 2;
    });
    for (int val : dst) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return 0;
}
```

A. 1 2 3 4 5  
B. 1 4 9 16 25  
C. 0 2 4 6 8  
D. 2 4 6 8 10

<!--
transform 将每个元素乘以 2 写入 dst：1→2, 2→4, 3→6, 4→8, 5→10，输出 "2 4 6 8 10"。
-->

## 解析

D 正确：`std::transform` 逐个读取 `src`，把 lambda 返回的 `x * 2` 写到 `dst` 对应位置。结果依次是 2、4、6、8、10。关键误区是认为 transform 会原地修改源容器；本题写入的是目标容器。
