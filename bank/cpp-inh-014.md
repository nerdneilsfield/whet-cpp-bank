---
qid: cpp-inh-014
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: C
---

以下代码能否编译通过？

```cpp
struct Base {
private:
    int x = 10;
};
struct Derived : public Base {
    void show() { std::cout << x; }  // 尝试访问基类 private 成员
};
```

A. 能，`public` 继承下派生类可以访问基类所有成员
B. 能，`private` 成员在派生类中变为 `protected`
C. 不能，基类 `private` 成员在派生类中不可访问
D. 能，但输出结果未定义
