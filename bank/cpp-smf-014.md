---
qid: cpp-smf-014
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: A
---

以下代码中，`Bar b2 = std::move(b1);` 调用的是哪个特殊成员函数？

```cpp
struct Bar {
    Bar() = default;
    Bar(const Bar&) = default;
    Bar(Bar&&) = default;
};
Bar b1;
Bar b2 = std::move(b1);
```

A. 移动构造函数
B. 拷贝构造函数
C. 拷贝赋值运算符
D. 默认构造函数
