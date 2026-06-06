---
qid: cpp-cpp17-014
type: fill
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "100"
---

# 代码阅读：make_unique 与解引用

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(100);
    std::cout << *p << "\n";
}
```

程序输出：`_______`

（填写整数结果，不含换行符）
