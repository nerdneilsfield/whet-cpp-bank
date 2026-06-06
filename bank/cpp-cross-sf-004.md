---
qid: cpp-cross-sf-004
type: single
kp: [cpp-scope-linkage, cpp-functions]
difficulty: easy
answer_key: A
---

以下代码连续调用 `next_id()` 三次，输出是什么？

```cpp
#include <iostream>

int next_id(int start = 1) {
    static int current = start;
    return current++;
}

int main() {
    std::cout << next_id() << " ";
    std::cout << next_id() << " ";
    std::cout << next_id(100) << std::endl;
    return 0;
}
```

A. 1 2 3  
B. 1 2 100  
C. 1 1 100  
D. 1 2 101

<!--
static 局部变量 current 仅在第一次进入函数时初始化（start 默认为 1）。
第一次调用：current 初始化为 1，返回 1，current 变为 2。
第二次调用：current 已存在（值为 2），不重新初始化，返回 2，current 变为 3。
第三次调用 next_id(100)：start=100，但 current 已初始化过，static 初始化器
不再执行，current 值仍为 3，返回 3，current 变为 4。
输出：1 2 3。
-->
