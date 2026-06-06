---
qid: cpp-tmpl-adv-006
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

给定以下代码：

```cpp
#include <type_traits>
#include <iostream>

template <typename T>
void check(T val) {
    if constexpr (std::is_same<T, int>::value) {
        std::cout << "int branch\n";
    } else {
        std::cout << "other branch\n";
    }
}

int main() {
    check(3.14);
}
```

程序输出是？

A. `int branch`
B. `other branch`
C. 编译错误
D. 运行时未定义行为
