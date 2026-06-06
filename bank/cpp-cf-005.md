---
qid: cpp-cf-005
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: B
---

以下代码发生了 `switch` fallthrough，输出是什么？

```cpp
#include <iostream>
int main() {
    int n = 1;
    switch (n) {
        case 1: std::cout << "A";
        case 2: std::cout << "B";
        case 3: std::cout << "C"; break;
        default: std::cout << "D";
    }
    return 0;
}
```

A. A
B. ABC
C. AB
D. ABCD

## Explanation

正确答案是 B。`n` 匹配 `case 1` 后输出 `A`，但该分支没有 `break`，会继续向下执行 `case 2` 和 `case 3`，依次输出 `B`、`C`。`case 3` 后的 `break` 阻止进入 `default`。
