---
qid: cpp-inh-011
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: C
---

以下代码的输出是什么？

```cpp
#include <iostream>
struct Base {
    Base() { std::cout << "Base"; }
};
struct Derived : public Base {
    Derived() : Base() { std::cout << "Derived"; }
};
int main() {
    Derived d;
}
```

A. `Derived`
B. `DerivedBase`
C. `BaseDerived`
D. 编译错误

## 解析

正确答案是 C，对应“BaseDerived”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“Derived”不满足题干要求；B 项“DerivedBase”不满足题干要求；D 项“编译错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
