---
qid: cpp-cf-med-001
type: single
kp: [cpp-control-flow]
difficulty: medium
answer_key: B
---
下列代码输出是？

```cpp
#include <iostream>
int main() {
    int x = 2;
    switch (x) {
        case 1: std::cout << "A";
        case 2: std::cout << "B";
        case 3: std::cout << "C"; break;
        default: std::cout << "D";
    }
    return 0;
}
```

A. B
B. BC
C. BCD
D. ABCD

---

**解析：**

`switch` 的 `case` 分支之间默认是顺序执行（fall-through），除非遇到 `break` 或 `return` 跳出。`x=2` 进入 `case 2`，打印 `B` 后继续执行 `case 3:` 的语句（因为 `case 2` 块内没有 `break`），打印 `C`，然后遇到 `break` 退出 `switch`。`default` 不被执行。所以输出是 `BC`。C++17 引入 `[[fallthrough]]` 属性以显式标记有意为之的 fallthrough。
