---
qid: cpp-friend-r-004
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: "B"
---

### 题目

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

## Explanation

正确答案是 B，输出 `(3, 4)`。重载的 `operator<<` 被声明为 `Point` 的友元，因此它虽是非成员函数，也能访问私有成员 `x` 和 `y`。A 项错误，流插入运算符常见写法正是非成员友元；C 项忽略了友元权限；D 项不是代码实际拼接出的字符串格式。
