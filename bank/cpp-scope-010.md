---
qid: cpp-scope-010
type: fill
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: "10"
---

# 变量遮蔽（shadowing）

阅读以下代码，填写输出结果：

```cpp
#include <iostream>

int x = 10;

int main() {
    std::cout << x << "\n";  // 行 A
    int x = 20;
    std::cout << x << "\n";  // 行 B
    {
        int x = 30;
        std::cout << x << "\n";  // 行 C
    }
    std::cout << x << "\n";  // 行 D
    return 0;
}
```

行 A 的输出是 ______。
