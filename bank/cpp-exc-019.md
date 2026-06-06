---
qid: cpp-exc-019
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: B
---

# C++ 异常处理：代码阅读——catch(...) 兜底

```cpp
#include <iostream>
int main() {
    try {
        throw 3.14;
    } catch (int i) {
        std::cout << "int\n";
    } catch (...) {
        std::cout << "other\n";
    }
}
```

输出是？

A. `int`
B. `other`（`double` 不匹配 `int`，落入 `catch(...)`）
C. 编译错误
D. 程序 `std::terminate()` 终止
