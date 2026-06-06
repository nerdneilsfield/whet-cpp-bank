---
qid: cpp-friend-014
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: C
---

下列代码能否编译通过？

```cpp
class A {
    int x = 10;
    friend class B;
};

class B {
public:
    void show(A a) {
        std::cout << a.x;  // 访问 A 的私有成员
    }
};
```

A. 不能，`B` 不能访问 `A` 的私有成员
B. 不能，`friend class` 语法错误
C. 能，`B` 是 `A` 的友元类，`B` 的所有成员函数都可访问 `A` 的私有成员
D. 能，但只有 `B` 的 `public` 成员函数才能访问 `A` 的私有成员
