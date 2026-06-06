---
qid: cpp-cross-me-005
type: single
kp: [cpp-memory-mgmt, cpp-exceptions]
difficulty: easy
answer_key: C
---

# 题目

```cpp
#include <iostream>
#include <memory>
#include <stdexcept>

struct A { ~A() { std::cout << "~A\n"; } };
struct B { ~B() { std::cout << "~B\n"; } };
struct C { ~C() { std::cout << "~C\n"; } };

void work() {
    auto pa = std::make_unique<A>();
    auto pb = std::make_unique<B>();
    auto pc = std::make_unique<C>();
    throw std::runtime_error("boom");
}

int main() {
    try { work(); } catch (...) {}
}
```

程序输出是？

A. `~A` → `~B` → `~C`

B. `~A` → `~C` → `~B`

C. `~C` → `~B` → `~A`

D. 输出顺序未定义

---

## Explanation

C++ 栈展开（stack unwinding）按**声明的逆序**销毁局部变量：最后声明的最先析构。

`pa` → `pb` → `pc` 依次声明，因此析构顺序为 `pc`（`~C`）→ `pb`（`~B`）→ `pa`（`~A`）。

选 **C**：`~C` → `~B` → `~A`。

这与普通作用域退出（无异常）的析构顺序**完全相同**——异常不改变析构规则，只是触发时机变为栈展开而非正常返回。
