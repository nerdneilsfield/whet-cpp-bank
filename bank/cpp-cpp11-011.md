---
qid: cpp-cpp11-011
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: A
---

# 代码阅读：范围 for 修改元素

阅读以下代码，输出是什么？

```cpp
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {1, 2, 3};
    for (auto& x : v) {
        x *= 2;
    }
    for (auto x : v) {
        std::cout << x << " ";
    }
}
```

A. `2 4 6`
B. `1 2 3`
C. 编译错误
D. 未定义行为
