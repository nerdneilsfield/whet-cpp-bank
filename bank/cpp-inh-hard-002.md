---
qid: cpp-inh-hard-002
type: single
kp: [cpp-inheritance]
difficulty: hard
answer_key: B
---

以下代码中 `D d;` 时构造函数调用次数及顺序是？

```cpp
#include <iostream>
struct A { A() { std::cout << "A "; } };
struct B : virtual A { B() { std::cout << "B "; } };
struct C : virtual A { C() { std::cout << "C "; } };
struct D : B, C { D() { std::cout << "D "; } };
```

A. `A A B C D `
B. `A B C D `
C. `B A C A D `
D. `A B A C D `

## Explanation

C++ 标准规定构造顺序：先**虚基类**（按深度优先、从左到右、唯一一次构造），再**非虚直接基类**（按声明顺序），最后**派生类自身**。`D` 的虚基为 `A`（被 `B`、`C` 共享），所以 `A` 只构造**一次**，并且由**最派生类** `D` 负责构造（而不是 `B` 或 `C`——它们的 `A()` 调用在虚继承下被抑制）。顺序为：`A` → `B` → `C` → `D`，输出 `A B C D `。C 错：`A` 不会被构造两次；D 错：同样问题。该规则消除了菱形继承中的二义性。
