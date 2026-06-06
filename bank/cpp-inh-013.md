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
