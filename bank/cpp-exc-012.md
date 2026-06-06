---
qid: cpp-exc-012
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: A
---

# C++ 异常处理：代码阅读——栈展开析构

```cpp
#include <iostream>
struct Guard {
    ~Guard() { std::cout << "~Guard\n"; }
};
void f() {
    Guard g;
    throw std::runtime_error("oops");
}
int main() {
    try { f(); }
    catch (...) { std::cout << "caught\n"; }
}
```

输出顺序是？

A. `~Guard` 然后 `caught`
B. `caught` 然后 `~Guard`
C. 只有 `caught`，Guard 析构不调用
D. 程序 `std::terminate()` 终止
