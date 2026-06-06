---
qid: cpp-operators-med-001
type: single
kp: [cpp-operators]
difficulty: medium
answer_key: A
---
下列代码输出是？

```cpp
#include <iostream>
int main() {
    int a = 6, b = 4, c = 4;
    std::cout << (a & b == c) << "\n";
    return 0;
}
```

A. 0
B. 1
C. 4
D. 6

---

**解析：**

运算符优先级陷阱：`==` 的优先级高于位与 `&`。表达式被解析为 `a & (b == c)`，而不是程序员通常期望的 `(a & b) == c`。这里 `b == c` 为 `true`（即 `1`），于是 `6 & 1`：`6` 是 `110`，`1` 是 `001`，按位与得 `000`，即 `0`。如果按期望的 `(6 & 4) == 4`，结果应是 `1`。结论：位运算与比较混用时务必加括号。
