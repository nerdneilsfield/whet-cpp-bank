---
qid: cpp-inh-013
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: D
---

以下代码是否合法？

```cpp
struct Animal {
    int age;
};
struct Dog : public Animal {};

int main() {
    Dog d;
    d.age = 5;  // 访问继承自 Animal 的 age
}
```

A. 不合法，派生类不能直接访问基类成员
B. 不合法，`age` 是 `public`，但继承后变为 `private`
C. 合法，但需要通过 `d.Animal::age` 访问
D. 合法，`public` 继承保留基类 `public` 成员的访问权限

## 解析

正确答案是 D，对应“合法，public 继承保留基类 public 成员的访问权限”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“不合法，派生类不能直接访问基类成员”不满足题干要求；B 项“不合法，age 是 public，但继承后变为 private”不满足题干要求；C 项“合法，但需要通过 d.Animal::age 访问”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
