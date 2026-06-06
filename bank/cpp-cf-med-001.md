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

## Explanation

正确答案为 B，因为“BC”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
