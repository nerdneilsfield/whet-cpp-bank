---
qid: cpp-tmp-hard-007
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: B
---

以下代码使用 C++17 fold 表达式打印所有参数：

```cpp
#include <iostream>

template<typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args);
}

int main() {
    print_all(1, 2, 3);
}
```

程序的输出是？

A. `1 2 3`（带空格）
B. `123`（无分隔符）
C. `321`（逆序）
D. 编译错误
