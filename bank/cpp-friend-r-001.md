---
qid: cpp-friend-r-001
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: "B"
---

## 题目

阅读以下代码，程序输出是什么？

```cpp
#include <iostream>

class Box {
    int value = 42;
    friend void reveal(const Box& b);
};

void reveal(const Box& b) {
    std::cout << b.value << std::endl;
}

int main() {
    Box b;
    reveal(b);
}
```

A. 编译错误：`value` 是 private，`reveal` 无法访问
B. `42`
C. `0`
D. 未定义行为

## 解析

`reveal` 被声明为 `Box` 的 friend 函数，因此它可以直接访问 `Box` 的 private 成员 `value`。输出为 `42`。friend 函数不是成员函数，但拥有访问 private/protected 成员的权限。
