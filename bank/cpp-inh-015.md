---
qid: cpp-inh-015
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

以下代码发生了什么问题？

```cpp
#include <iostream>
struct Shape {
    int color = 1;
    void draw() { std::cout << "Shape"; }
};
struct Circle : public Shape {
    int radius = 5;
};

int main() {
    Circle c;
    Shape s = c;  // 派生类对象赋值给基类对象
    std::cout << s.radius;  // 尝试访问 radius
}
```

A. 正常输出 `5`
B. 编译错误，`Shape` 没有 `radius` 成员
C. 运行时崩溃
D. 输出 `0`
