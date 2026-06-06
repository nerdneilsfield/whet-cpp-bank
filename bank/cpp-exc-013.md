---
qid: cpp-exc-013
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: D
---

# C++ 异常处理：代码阅读——noexcept 抛异常

```cpp
#include <iostream>
void safe() noexcept {
    throw std::runtime_error("bad");
}
int main() {
    try {
        safe();
    } catch (...) {
        std::cout << "caught\n";
    }
    return 0;
}
```

程序运行结果是？

A. 输出 `caught`
B. 编译错误，noexcept 函数不能含 throw
C. 静默忽略异常，正常退出
D. 调用 `std::terminate()`，程序异常终止
