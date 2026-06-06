---
qid: cpp-cross-me-001
type: single
kp: [cpp-memory-mgmt, cpp-exceptions]
difficulty: easy
answer_key: B
---

# 题目

```cpp
#include <iostream>
#include <memory>
#include <stdexcept>

struct Res {
    Res()  { std::cout << "Res()\n"; }
    ~Res() { std::cout << "~Res()\n"; }
};

void foo() {
    auto p = std::make_unique<Res>();
    throw std::runtime_error("oops");
}

int main() {
    try {
        foo();
    } catch (...) {
        std::cout << "caught\n";
    }
}
```

以下哪项描述了该程序的**完整输出**？

A. `Res()` → `caught`（析构未被调用，unique_ptr 泄漏）

B. `Res()` → `~Res()` → `caught`

C. `Res()` → `caught` → `~Res()`

D. 程序崩溃，无输出

---

## 解析

`unique_ptr` 是 RAII 对象，存储在栈上。
`foo()` 抛出异常时，C++ 运行时进行**栈展开**（stack unwinding），`foo()` 的所有栈帧局部变量被销毁，`p` 的析构函数在控制流离开 `foo()` 之前被调用。
因此析构消息在 `caught` 之前打印，选 **B**。
