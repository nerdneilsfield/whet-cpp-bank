---
qid: cpp-cast-009
type: fill
kp: [cpp-casting]
difficulty: easy
answer_key: "3"
---

# static_cast 截断行为

```cpp
#include <iostream>
int main() {
    double x = 3.9;
    int y = static_cast<int>(x);
    std::cout << y;
}
```

程序输出是：___
