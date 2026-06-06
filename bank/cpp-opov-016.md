---
qid: cpp-opov-016
type: fill
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "return !(*this == rhs);"
---

已知类 `Point` 已定义 `operator==`，请用最简洁的方式实现 `operator!=`，补全函数体：

```cpp
struct Point {
    int x, y;
    bool operator==(const Point& rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const Point& rhs) const {
        ______
    }
};
```
