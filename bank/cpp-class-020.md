---
qid: cpp-class-020
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: D
---

以下结构体聚合初始化，哪项是正确的？

```cpp
struct Point {
    int x;
    int y;
};
```

A. `Point p = Point(1, 2);`
B. `Point p; p = {1, 2};`（仅 C++11 之前）
C. `Point p(1, 2);`
D. `Point p = {1, 2};`
