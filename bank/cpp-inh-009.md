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

## Explanation

正确答案是 A，对应“能，age 是 protected，派生类 Dog 可访问”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：B 项“不能，protected 成员不能在派生类成员函数内访问”不满足题干要求；C 项“能，但 age 值为 0”不满足题干要求；D 项“不能，age 未显式声明为 public”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
