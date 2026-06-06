---
qid: cpp-smf-012
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: C
---

以下代码中，`f2 = f1;` 调用的是哪个特殊成员函数？

```cpp
struct Foo { int x; };
Foo f1{42};
Foo f2{0};
f2 = f1;
```

A. 默认构造函数
B. 拷贝构造函数
C. 拷贝赋值运算符
D. 移动赋值运算符
