---
qid: cpp-exc-017
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: A
---

# C++ 异常处理：代码阅读——抛出自定义类型

```cpp
#include <iostream>
struct MyError {
    const char* msg;
    MyError(const char* m) : msg(m) {}
};
int main() {
    try {
        throw MyError("custom");
    } catch (MyError& e) {
        std::cout << e.msg << "\n";
    } catch (...) {
        std::cout << "unknown\n";
    }
}
```

输出是？

A. `custom`
B. `unknown`
C. 编译错误，自定义类型不能抛出
D. 程序终止
