---
qid: cpp-exc-r-004
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: B
---

### 题目

下面代码的输出是什么？

```cpp
#include <iostream>
#include <stdexcept>

void rethrow() {
    try {
        throw std::runtime_error("original");
    } catch (std::exception& e) {
        std::cout << "inner: " << e.what() << "\n";
        throw;   // 重新抛出
    }
}

int main() {
    try {
        rethrow();
    } catch (std::runtime_error& e) {
        std::cout << "outer runtime_error: " << e.what() << "\n";
    } catch (std::exception& e) {
        std::cout << "outer exception: " << e.what() << "\n";
    }
}
```

A. inner: original  /  outer exception: original
B. inner: original  /  outer runtime_error: original
C. 只输出  outer runtime_error: original
D. 编译错误

## Explanation

B


不带操作数的 `throw;` 重新抛出**当前正在处理的异常对象**，保留其原始类型和值，不创建副本。本例中原始异常是 `std::runtime_error`，重新抛出后外层 `catch (std::runtime_error&)` 精确匹配，输出第二行。如果写 `throw e;`（抛出副本）则会发生**对象切片**，抛出的是 `std::exception` 副本，外层会匹配 `catch (std::exception&)`。
