---
qid: cpp-opov-r-003
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "A"
---

### 题目

以下代码能否编译并正确运行？输出是什么？

```cpp
#include <iostream>

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }
};

int main() {
    Point a(1, 2), b(3, 4);
    std::cout << a << b << "\n";
}
```

A. 编译通过，输出 `(1,2)(3,4)`
B. 编译通过，输出 `(3,4)(1,2)`（右结合，先输出 `b`）
C. 编译错误，`operator<<` 不能声明为 `friend`
D. 编译错误，不能在同一语句连续使用 `<<`

## Explanation

`operator<<` 返回 `std::ostream&`，使链式调用成为可能。`<<` 是左结合运算符，因此 `std::cout << a << b` 等价于 `(std::cout << a) << b`，先输出 `a` 再输出 `b`。输出 `(1,2)(3,4)\n`。
