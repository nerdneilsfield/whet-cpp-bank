---
qid: cpp-cont-r-004
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: "C"
---

## 题目

以下代码输出什么？

```cpp
#include <stack>
#include <iostream>

int main() {
    std::stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << s.top() << std::endl;
    s.pop();
    s.push(99);
    std::cout << s.top() << std::endl;
}
```

A. `10` / `20`
B. `30` / `20`
C. `30` / `99`
D. `10` / `99`

## 解析

`std::stack` 是后进先出（LIFO）结构。push 10、20、30 后，`top()` 返回最后入栈的 `30`；`pop()` 移除 `30`，栈顶变为 `20`；再 `push(99)` 后 `top()` 返回 `99`。
