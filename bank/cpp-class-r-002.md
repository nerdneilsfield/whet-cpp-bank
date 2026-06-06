---
qid: cpp-class-r-002
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: B
---

# 代码阅读：静态成员跨对象共享

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
struct Counter {
    static int count;
    Counter() { ++count; }
};
int Counter::count = 0;

int main() {
    Counter a, b, c;
    std::cout << Counter::count;
    return 0;
}
```

A. `0`  
B. `3`  
C. 编译错误：`count` 未在类外定义  
D. 每个对象各有一份 `count`，输出 `1`
