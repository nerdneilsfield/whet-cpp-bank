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

## Explanation

正确答案是 C，对应“能，B 是 A 的友元类，B 的所有成员函数都可访问 A 的私有成员”。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。其他选项容易混淆相关概念：A 项“不能，B 不能访问 A 的私有成员”不满足题干要求；B 项“不能，friend class 语法错误”不满足题干要求；D 项“能，但只有 B 的 public 成员函数才能访问 A 的私有成员”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
