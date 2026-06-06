---
qid: cpp-func-r-001
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: C
---

# 代码阅读：默认参数顺序错误

以下代码能否编译通过？

```cpp
#include <iostream>
void greet(std::string name = "World", std::string prefix) {
    std::cout << prefix << " " << name;
}
int main() {
    greet("Alice", "Hello");
    return 0;
}
```

A. 编译通过，输出 `Hello Alice`
B. 编译通过，输出 `World Hello`
C. 编译失败，有默认值的参数必须在参数列表末尾
D. 运行时错误
