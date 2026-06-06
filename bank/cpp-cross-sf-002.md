---
qid: cpp-cross-sf-002
type: single
kp: [cpp-scope-linkage, cpp-functions]
difficulty: easy
answer_key: D
---

以下代码的编译结果是什么？

```cpp
#include <iostream>
#include <algorithm>

int max = 100;   // global variable named max

void print_max(int a, int b) {
    int max = std::max(a, b);   // local variable shadows global max
    std::cout << max << std::endl;
}

int main() {
    print_max(3, 7);
    return 0;
}
```

A. 编译错误：`max` 重复定义  
B. 编译错误：`std::max` 被全局 `max` 遮蔽，无法调用  
C. 运行时输出 100  
D. 正常编译，输出 7

<!--
局部变量 int max 在 print_max 函数体内遮蔽全局 max，但 std::max 是受命名空间
限定的调用，不受遮蔽影响。std::max(3,7) 返回 7，赋给局部 max，输出 7。
注意：若写成无限定的 max(a,b) 才会产生歧义或错误。
-->
