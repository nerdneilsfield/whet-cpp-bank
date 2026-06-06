---
qid: cpp-scope-011
type: multi
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: [B, D]
---

# 变量遮蔽完整输出

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

下列哪些选项**正确**描述了该程序的输出？（多选）

A. 行 B 输出 10
B. 行 B 输出 20
C. 行 C 输出 20
D. 行 D 输出 20
