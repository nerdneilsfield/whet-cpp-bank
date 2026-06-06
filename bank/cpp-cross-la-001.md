---
qid: cpp-cross-la-001
type: single
kp: [cpp-lambdas, cpp-algorithms]
difficulty: easy
answer_key: C
---

以下代码输出是什么？

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
    std::sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });
    std::cout << v[0] << std::endl;
    return 0;
}
```

A. 1  
B. 3  
C. 9  
D. 6

<!--
std::sort 使用降序 lambda 比较器，排序后最大值在首位，v[0] = 9。
-->
