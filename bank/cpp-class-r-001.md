---
qid: cpp-class-r-001
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: C
---

# 代码阅读：成员初始化列表顺序

阅读以下代码，推断输出结果（成员按**声明顺序**初始化，而非列表书写顺序）：

```cpp
#include <iostream>
struct Foo {
    int a;
    int b;
    Foo() : b(1), a(b + 1) {}
};
int main() {
    Foo f;
    std::cout << f.a << " " << f.b;
    return 0;
}
```

A. `2 1`  
B. `1 1`  
C. 未定义行为：`a` 先初始化，此时 `b` 未初始化，`b+1` 的值不确定  
D. 编译错误：初始化列表顺序必须与声明顺序一致
