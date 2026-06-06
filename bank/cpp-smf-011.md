---
qid: cpp-smf-011
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: B
---

以下代码中，`Foo f2 = f1;` 调用的是哪个特殊成员函数？

```cpp
struct Foo { int x; };
Foo f1{42};
Foo f2 = f1;
```

A. 默认构造函数
B. 拷贝构造函数
C. 拷贝赋值运算符
D. 移动构造函数
