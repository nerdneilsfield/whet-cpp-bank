---
qid: cpp-cont-012
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: B
---

阅读以下代码，输出是什么？

```cpp
#include <map>
#include <iostream>
int main() {
    std::map<std::string, int> m;
    std::cout << m["x"] << std::endl;
    std::cout << m.size() << std::endl;
}
```

A. `0` 然后 `0`
B. `0` 然后 `1`
C. 运行时错误
D. 编译错误
