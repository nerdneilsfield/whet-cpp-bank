---
qid: cpp-friend-015
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: B
---

下列代码能否编译通过？

```cpp
class A {
    int x = 5;
    friend class B;
};

class B {
    int y = 10;
};

class C {
public:
    void test(A a, B b) {
        std::cout << a.x;  // C 访问 A 的私有成员
    }
};
```

A. 能，因为 B 是 A 的友元，C 继承了这个关系
B. 不能，C 不是 A 的友元，不能访问 `a.x`
C. 能，`friend` 关系可以传递给第三方类
D. 能，`x` 虽然私有，但通过 B 的中转可以访问
