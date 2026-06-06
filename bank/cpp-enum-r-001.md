---
qid: cpp-enum-r-001
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---

### 题目

下面代码能否通过编译？若能，输出是什么？

```cpp
#include <iostream>

enum class Color { Red, Green, Blue };

int main() {
    Color c = Green;
    std::cout << "ok" << std::endl;
    return 0;
}
```

A. 输出 `ok`
B. 编译错误：`Green` 未声明
C. 输出 `1`
D. 运行时崩溃

## Explanation

B


`enum class` 的成员必须通过作用域访问，即 `Color::Green`。直接使用 `Green` 会导致编译错误：`'Green' was not declared in this scope`。这是 `enum class` 相对于传统 `enum` 最显著的区别之一。
