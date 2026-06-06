---
qid: cpp-cross-sf-005
type: single
kp: [cpp-scope-linkage, cpp-functions]
difficulty: easy
answer_key: B
---

以下代码输出是什么？

```cpp
#include <iostream>

static int double_val(int x) {
    return x * 2;
}

int main() {
    int (*fp)(int) = double_val;   // take address of static function
    std::cout << fp(5) << std::endl;
    return 0;
}
```

A. 编译错误：static 函数不能取地址  
B. 10  
C. 链接错误：static 函数仅限内部链接，函数指针无法引用  
D. 未定义行为

<!--
static 函数具有内部链接，意味着它在翻译单元外不可见，但在同一翻译单元内
完全可以取地址并通过函数指针调用。fp = double_val 合法，fp(5) 调用 double_val(5)
返回 10。内部链接只限制跨翻译单元的可见性，不限制本单元内的使用。
-->
