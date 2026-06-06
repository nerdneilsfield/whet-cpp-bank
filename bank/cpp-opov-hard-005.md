---
qid: cpp-opov-hard-005
type: single
kp: [cpp-operator-overload]
difficulty: hard
answer_key: C
---

关于 ADL（参数依赖查找）与运算符重载的关系，下列代码的行为是？

```cpp
namespace nsa {
    struct A {};
    A operator+(const A&, const A&) { return {}; }
}

namespace nsb {
    void use() {
        nsa::A x, y;
        auto z = x + y;     // ① 能调用 nsa::operator+ 吗？
    }
}
```

A. 失败：`operator+` 不在 `nsb` 中且未 `using`
B. 失败：运算符重载必须显式 `using namespace`
C. 成功：运算符 `+` 的查找采用普通查找 + **ADL**——`x` 和 `y` 的类型 `nsa::A` 属于 `nsa`，编译器自动把 `nsa` 加入查找作用域，找到 `nsa::operator+`。这是为何 `<<`、`==` 等运算符跨命名空间能"开箱即用"的原因
D. 仅当 `using namespace nsa;` 时才能使用

## 解析

ADL（Koenig Lookup / Argument-Dependent Lookup）是 C++ 中名字查找的重要扩展：当查找非成员函数时，除常规作用域外，编译器还会在**实参类型所属的命名空间**中查找。运算符重载是 ADL 最常见的用例——这正是为什么自定义类型的 `operator<<` 放在类型自己的命名空间里，用户在任意位置写 `std::cout << myObj` 都能找到。

具体规则：对 `x + y`，编译器分别取实参类型，向上爬至最内命名空间，把这些命名空间加入"关联命名空间集"，在其中查找符合签名的函数。本例中 `nsa::A` 把 `nsa` 加入查找集，发现 `nsa::operator+`，调用成功。

陷阱：ADL 也是 `std::swap` 习语（`using std::swap; swap(a,b);`）的基础，让用户自定义的 `swap` 能优先被找到；但同时可能导致意外重载被选中——经典案例如 `std::move` 与用户命名空间的 `move` 冲突。