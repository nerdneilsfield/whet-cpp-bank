---
qid: cpp-cf-r-003
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: C
---

# 代码阅读：for 循环变量作用域

以下代码能否编译通过？

```cpp
#include <iostream>
int main() {
    for (int i = 0; i < 3; i++) {
        std::cout << i;
    }
    std::cout << i;  // 使用循环变量
    return 0;
}
```

A. 编译通过，输出 `0123`
B. 编译通过，输出 `012` 后打印未定义值
C. 编译失败，`i` 在循环外不可见
D. 运行时错误
