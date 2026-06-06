---
qid: cpp-cross-sf-001
type: single
kp: [cpp-scope-linkage, cpp-functions]
difficulty: easy
answer_key: B
---

以下代码输出是什么？

```cpp
#include <iostream>

int count_calls() {
    static int n = 0;
    ++n;
    if (n < 4) count_calls();
    return n;
}

int main() {
    int r = count_calls();
    std::cout << r << std::endl;
    return 0;
}
```

A. 1  
B. 4  
C. 3  
D. 每次输出不同

<!--
static 局部变量 n 只初始化一次，所有递归帧共享同一份存储。
第一次调用 n→1，递归到 n→2→3→4；n==4 时不再递归，逐层返回均返回当前 n 值 4。
因此最终输出 4。
-->

## Explanation

B 正确：函数内的 `static` 局部变量只初始化一次，所有递归调用共享同一个 `n`，而不是每个栈帧各有一份。第一次调用后递归连续把 n 增加到 4，随后停止递归。逐层返回时读到的仍是同一个当前值 4，不会恢复旧值，所以最终输出 4。
