---
qid: cpp-mem-016
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: B
---

# 阅读代码，判断输出

```cpp
#include <memory>
#include <iostream>

struct Foo {
    Foo()  { std::cout << "C"; }
    ~Foo() { std::cout << "D"; }
};

int main() {
    {
        auto p = std::make_unique<Foo>();
    }   // p 离开作用域
    std::cout << "X";
}
```

程序输出是？

A. `CX`
B. `CDX`
C. `CXD`
D. `CDX` 之后崩溃

<!--
unique_ptr 离开作用域触发析构，Foo 析构函数输出 D，
随后执行 cout << "X"。输出：CDX。答案 B。
-->

## 解析

正确答案是 B，`make_unique<Foo>()` 先构造 `Foo` 输出 `C`。内部作用域结束时 `unique_ptr` 析构并删除对象，`Foo::~Foo` 输出 `D`，随后程序继续输出 `X`。这正体现了 RAII：资源释放发生在所有者离开作用域时，而不是等到 `main` 结束。
