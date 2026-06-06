---
qid: cpp-cpp11-015
type: fill
kp: [cpp-cpp11]
difficulty: easy
answer_key: "5"
---

# 代码阅读：initializer_list 求和

阅读以下代码，输出是多少？

```cpp
#include <iostream>
#include <initializer_list>

int sum(std::initializer_list<int> lst) {
    int s = 0;
    for (auto v : lst) s += v;
    return s;
}

int main() {
    std::cout << sum({1, 2, 2});
}
```

输出为：___
