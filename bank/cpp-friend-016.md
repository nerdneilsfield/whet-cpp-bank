---
qid: cpp-friend-016
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: A
---

阅读以下代码，判断输出结果：

```cpp
#include <iostream>
class Point {
    double x, y;
public:
    Point(double x, double y) : x(x), y(y) {}
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

int main() {
    Point p(1.0, 2.0);
    std::cout << p;
}
```

A. `(1,2)`
B. 编译错误，`operator<<` 不能访问私有成员 `x`、`y`
C. 编译错误，`operator<<` 必须是成员函数
D. `Point(1,2)`
