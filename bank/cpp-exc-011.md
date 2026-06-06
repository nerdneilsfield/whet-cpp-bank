---
qid: cpp-exc-011
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: C
---

# C++ 异常处理：代码阅读——输出结果

```cpp
#include <iostream>
int main() {
    try {
        throw 42;
    } catch (double d) {
        std::cout << "double: " << d << "\n";
    } catch (int i) {
        std::cout << "int: " << i << "\n";
    }
    return 0;
}
```

上述代码的输出是？

A. `double: 42`
B. 编译错误
C. `int: 42`
D. 程序终止，无输出
