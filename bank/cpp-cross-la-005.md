---
qid: cpp-cross-la-005
type: fill
kp: [cpp-lambdas, cpp-algorithms]
difficulty: easy
answer_key: "15"
---

以下代码的输出结果是什么？（填写输出的整数值）

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    int sum = 0;
    std::for_each(v.begin(), v.end(), [&sum](int x) {
        sum += x;
    });
    std::cout << sum << std::endl;
    return 0;
}
```

<!--
lambda 以引用方式捕获 sum，for_each 遍历每个元素累加：1+2+3+4+5 = 15。
-->
