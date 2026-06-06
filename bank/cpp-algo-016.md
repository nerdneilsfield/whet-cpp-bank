---
qid: cpp-algo-016
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: C
---

以下代码的输出是什么？

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9};
    auto it = std::min_element(v.begin(), v.end());
    std::cout << *it << std::endl;
}
```

A. 3
B. 9
C. 1
D. 4
