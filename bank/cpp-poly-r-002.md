---
qid: cpp-poly-r-002
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: "C"
---

### 题目

阅读以下代码，运行后输出是什么？（注意：析构函数**不是** virtual）

```cpp
#include <iostream>

struct Base {
    ~Base() { std::cout << "~Base\n"; }
};

struct Derived : Base {
    ~Derived() { std::cout << "~Derived\n"; }
};

int main() {
    Base* p = new Derived();
    delete p;
}
```

A. `~Derived` 然后 `~Base`
B. `~Base` 然后 `~Derived`
C. 只输出 `~Base`
D. 只输出 `~Derived`

## Explanation

`Base` 的析构函数不是虚函数，`delete p` 静态绑定到 `Base::~Base()`，只调用基类析构，`Derived::~Derived()` 永远不会被调用。这是经典的内存泄漏/未定义行为场景。修复方法：将 `Base` 的析构函数声明为 `virtual`。
