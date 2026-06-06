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

## Explanation

正确答案是 C。`throw` 表达式用于抛出异常；在 `catch` 中单独写 `throw;` 表示重新抛出当前异常。选项 C 的表述“｀int: 42｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
