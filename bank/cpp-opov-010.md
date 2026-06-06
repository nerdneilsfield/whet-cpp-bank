---
qid: cpp-opov-010
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: B
---

下列代码能否通过编译？

```cpp
class Foo {
public:
    int operator?:(bool cond, int a, int b);
};
```

A. 能，这是合法的运算符重载
B. 不能，`?:` 不可被重载
C. 不能，`?:` 只能被重载为非成员函数
D. 能，但只有在 C++17 之后才合法
