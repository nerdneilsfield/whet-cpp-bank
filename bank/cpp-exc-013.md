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

## Explanation

正确答案是 D。`noexcept` 是不抛异常承诺；异常若逃出该函数会调用 `std::terminate`。选项 D 的表述“调用 ｀std::terminate()｀，程序异常终止”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
