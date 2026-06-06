---
qid: cpp-tmp-med-009
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: C
---

以下代码中，`obj.print()` 的输出是什么？

```cpp
#include <iostream>
#include <string>

template<typename Derived>
struct Printer {
    void print() {
        static_cast<Derived*>(this)->impl();
    }
};

struct English : Printer<English> {
    void impl() { std::cout << "Hello" << std::endl; }
};

struct Chinese : Printer<Chinese> {
    void impl() { std::cout << "你好" << std::endl; }
};

void greet(Printer<Chinese>& obj) {
    obj.print();
}

int main() {
    Chinese c;
    greet(c);
}
```

A. `Hello`
B. 编译错误
C. `你好`
D. 无输出

---

**解析：**

`greet` 接受 `Printer<Chinese>&`，传入 `Chinese c`（`Chinese` 继承自 `Printer<Chinese>`），合法。  
`obj.print()` → `static_cast<Chinese*>(&obj)->impl()` → `Chinese::impl()` → 输出 `你好`。  
CRTP 向下转型在此处安全，因为 `obj` 的动态类型确实是 `Chinese`。

## Explanation

正确答案是 C，即 `你好`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
