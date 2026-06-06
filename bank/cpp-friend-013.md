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
