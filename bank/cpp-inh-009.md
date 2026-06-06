---
qid: cpp-inh-009
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: A
---

以下代码能否编译通过？

```cpp
class Animal {
protected:
    int age = 3;
};

class Dog : public Animal {
public:
    void show() { std::cout << age; }
};
```

A. 能，`age` 是 `protected`，派生类 `Dog` 可访问
B. 不能，`protected` 成员不能在派生类成员函数内访问
C. 能，但 `age` 值为 0
D. 不能，`age` 未显式声明为 `public`
