---
qid: cpp-cf-r-005
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: C
---

# 代码阅读：悬空 else 归属

阅读以下代码，当 `x = 0, y = 1` 时输出什么？

```cpp
#include <iostream>
int main() {
    int x = 0, y = 1;
    if (x > 0)
        if (y > 0)
            std::cout << "A";
        else
            std::cout << "B";
    std::cout << "C";
    return 0;
}
```

A. `A`
B. `B`
C. `C`
D. `BC`

## 解析

正确答案是 C。悬空 `else` 会绑定到最近的未匹配 `if`，也就是内层 `if (y > 0)`；但外层条件 `x > 0` 为假，所以整个嵌套 `if` 都不执行。最后独立的 `std::cout << "C"` 执行，输出 `C`。
