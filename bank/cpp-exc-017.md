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

## 解析

正确答案是 A。`throw` 表达式用于抛出异常；在 `catch` 中单独写 `throw;` 表示重新抛出当前异常。选项 A 的表述“｀custom｀”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
