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

## Explanation

正确答案是 C，对应“不能，基类 private 成员在派生类中不可访问”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“能，public 继承下派生类可以访问基类所有成员”不满足题干要求；B 项“能，private 成员在派生类中变为 protected”不满足题干要求；D 项“能，但输出结果未定义”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
