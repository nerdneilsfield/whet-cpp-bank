---
qid: cpp-cont-011
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: C
---

阅读以下代码，输出是什么？

```cpp
#include <map>
#include <iostream>
int main() {
    std::map<std::string, int> m;
    m["a"] = 1;
    m["b"] = 2;
    m["c"] = 3;
    for (auto& [k, v] : m) {
        std::cout << k << v;
    }
}
```

A. `c3b2a1`
B. 输出顺序不确定
C. `a1b2c3`
D. 编译错误
