---
qid: cpp-cross-la-002
type: single
kp: [cpp-lambdas, cpp-algorithms]
difficulty: easy
answer_key: B
---

以下代码输出是什么？

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 3, 7, 4, 9, 2};
    auto it = std::find_if(v.begin(), v.end(), [](int x) {
        return x % 2 == 0;
    });
    if (it != v.end()) {
        std::cout << *it << std::endl;
    }
    return 0;
}
```

A. 2  
B. 4  
C. 7  
D. 9

<!--
find_if 从左到右找第一个满足 x%2==0 的元素：1(奇)、3(奇)、7(奇)、4(偶) → 返回指向 4 的迭代器，*it = 4。
-->
