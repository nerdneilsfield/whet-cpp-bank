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

## 解析

正确答案是 B，对应“编译错误，Shape 没有 radius 成员”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“正常输出 5”不满足题干要求；C 项“运行时崩溃”不满足题干要求；D 项“输出 0”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
