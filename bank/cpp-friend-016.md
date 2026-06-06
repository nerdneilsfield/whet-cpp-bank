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

## 解析

正确答案是 A，对应“(1,2)”。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。其他选项容易混淆相关概念：B 项“编译错误，operator<< 不能访问私有成员 x、y”不满足题干要求；C 项“编译错误，operator<< 必须是成员函数”不满足题干要求；D 项“Point(1,2)”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
