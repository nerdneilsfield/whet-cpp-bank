---
qid: cpp-poly-r-004
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: "A"
---

### 题目

阅读以下代码，运行后输出是什么？

```cpp
#include <iostream>

struct Base {
    virtual void greet() { std::cout << "Base\n"; }
};

struct Derived : Base {
    // 注意：参数类型不同，拼写有误
    void greet(int x) { std::cout << "Derived\n"; }
};

int main() {
    Base* p = new Derived();
    p->greet();
    delete p;
}
```

A. `Base`
B. `Derived`
C. 编译错误
D. 链接错误

## Explanation

`Derived::greet(int)` 的签名与 `Base::greet()` **不同**（多了一个 `int` 参数），因此并没有覆盖（override）基类的虚函数，而是引入了一个新的重载函数。`p->greet()` 仍然调用 `Base::greet()`，输出 `Base`。若写成 `void greet() override` 编译器会立即发现签名不匹配并报错，这正是 `override` 关键字的价值所在。
