---
qid: cpp-operators-r-002
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: A
---

# 代码阅读：位运算优先级陷阱

```cpp
#include <iostream>
int main() {
    int a = 2, b = 3, c = 1;
    if (a & b == c)
        std::cout << "true\n";
    else
        std::cout << "false\n";
}
```

输出是什么？（注意：`==` 的优先级高于 `&`）

A. `false`（等价于 `a & (b == c)`，即 `2 & 0 == 0`，结果为 `false`）  
B. `true`（等价于 `(a & b) == c`，即 `2 == 1`，结果为 `false`——也不对）  
C. 编译错误  
D. `true`（因为 `2 & 3 == 1` 为真）

> 陷阱提示：`==` 优先级高于 `&`，实际求值顺序为 `a & (b == c)`。
