---
qid: cpp-class-017
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: A
---

以下代码中，`Circle::getR()` 在类外定义，其中 `::` 的作用是？

```cpp
double Circle::getR() const {
    return radius;
}
```

A. 指明 `getR` 是 `Circle` 类的成员函数
B. 访问 `Circle` 的静态变量
C. 表示继承关系
D. 调用父类构造函数
