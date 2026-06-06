---
qid: cpp-friend-r-004
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: "B"
---

## 题目

阅读以下代码，程序输出是什么？

```cpp
#include <iostream>

class Point {
    double x, y;
public:
    Point(double x, double y) : x(x), y(y) {}
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

int main() {
    Point pt(3.0, 4.0);
    std::cout << pt << std::endl;
}
```

A. 编译错误：`operator<<` 不能是 friend
B. `(3, 4)`
C. 编译错误：`p.x` 和 `p.y` 是 private，无法访问
D. `Point(3, 4)`

## 解析

将 `operator<<` 声明为 `Point` 的 friend，使其可以访问 private 成员 `x` 和 `y`。`std::cout << pt` 调用该重载，输出 `(3, 4)`。这是 C++ 中重载流输出运算符的惯用写法。
