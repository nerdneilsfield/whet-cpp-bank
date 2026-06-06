---
qid: cpp-inh-012
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

以下代码的输出是什么？

```cpp
#include <iostream>
struct Base {
    void greet() { std::cout << "Base"; }
};
struct Derived : public Base {
    void greet() { std::cout << "Derived"; }
};
int main() {
    Base* p = new Derived();
    p->greet();
    delete p;
}
```

A. `Derived`
B. `Base`
C. `BaseDerived`
D. 未定义行为

## Explanation

正确答案是 B，对应“Base”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“Derived”不满足题干要求；C 项“BaseDerived”不满足题干要求；D 项“未定义行为”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
