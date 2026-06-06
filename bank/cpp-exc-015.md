---
qid: cpp-exc-015
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: C
---

# C++ 异常处理：代码阅读——catch 匹配顺序（基类优先）

```cpp
#include <iostream>
#include <stdexcept>
int main() {
    try {
        throw std::runtime_error("re");
    } catch (std::exception& e) {
        std::cout << "exception\n";
    } catch (std::runtime_error& e) {
        std::cout << "runtime_error\n";
    }
}
```

输出是？

A. `runtime_error`
B. `exception` 然后 `runtime_error`
C. `exception`（基类 catch 先匹配，子类 catch 不可达）
D. 编译错误
