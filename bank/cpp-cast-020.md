---
qid: cpp-cast-020
type: multi
kp: [cpp-casting]
difficulty: easy
answer_key: [B, C]
---

# 代码阅读：输出与错误判断

```cpp
#include <iostream>
struct Base { virtual ~Base() {} };
struct D1 : Base { void hello() { std::cout << "D1"; } };
struct D2 : Base { void hello() { std::cout << "D2"; } };

int main() {
    Base* b = new D1();

    // 片段 A
    D2* p2 = static_cast<D2*>(b);         // 行1
    if (p2) p2->hello();                   // 行2

    // 片段 B
    D2* p3 = dynamic_cast<D2*>(b);        // 行3
    if (p3) p3->hello(); else std::cout << "null"; // 行4
}
```

下列说法哪些正确？（多选）

A. 行1 产生编译错误，`static_cast` 不能在无关派生类间转换
B. 行1 编译通过，但行2 调用 `p2->hello()` 是未定义行为
C. 行3 返回 `nullptr`，行4 输出 `null`
D. 行3 返回非空指针，行4 输出 `D2`

## 解析

正确答案是 B、C。`static_cast<D2*>(b)` 在语法上可从多态基类指针向下转到派生类指针，但不会检查实际对象类型；这里实际对象是 `D1`，用作 `D2` 调用成员函数是未定义行为。`dynamic_cast<D2*>(b)` 会检查失败并返回 `nullptr`，因此输出 `null`。
