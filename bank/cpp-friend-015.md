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

## 解析

正确答案是 B，对应“不能，C 不是 A 的友元，不能访问 a.x”。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。其他选项容易混淆相关概念：A 项“能，因为 B 是 A 的友元，C 继承了这个关系”不满足题干要求；C 项“能，friend 关系可以传递给第三方类”不满足题干要求；D 项“能，x 虽然私有，但通过 B 的中转可以访问”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
