---
qid: cpp-friend-013
type: fill
kp: [cpp-friend]
difficulty: easy
answer_key: "2（每次调用 increment 使 count 加 1，调用两次后 count == 2）"
---

阅读以下代码，`main` 结束时 `c.count` 的值是 ______？

```cpp
#include <iostream>
class Counter {
    int count = 0;
    friend void increment(Counter& c);
    friend int getCount(const Counter& c);
};

void increment(Counter& c) { c.count++; }
int getCount(const Counter& c) { return c.count; }

int main() {
    Counter c;
    increment(c);
    increment(c);
}
```

## 解析

应填写 `2（每次调用 increment 使 count 加 1，调用两次后 count == 2）`。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
