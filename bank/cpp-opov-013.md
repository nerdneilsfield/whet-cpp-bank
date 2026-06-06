---
qid: cpp-opov-013
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: A
---

以下代码中，`++c` 调用的是哪个版本的 `operator++`，`c.v` 变为多少？

```cpp
struct Counter {
    int v = 0;
    Counter& operator++() { ++v; return *this; }
    Counter  operator++(int) { Counter t = *this; ++v; return t; }
};

Counter c;
Counter& r = ++c;
```

A. 调用前置版本；`c.v = 1`，`r` 与 `c` 是同一对象
B. 调用后置版本；`c.v = 1`，`r` 是临时副本
C. 调用前置版本；`c.v = 0`，`r` 是临时副本
D. 编译错误，前置 `++` 不返回引用
