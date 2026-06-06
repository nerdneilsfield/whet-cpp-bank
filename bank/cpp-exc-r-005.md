---
qid: cpp-exc-r-005
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: B
---

### 题目

下面代码的输出是什么？

```cpp
#include <iostream>

int main() {
    try {
        throw 42;
    } catch (double d) {
        std::cout << "double: " << d << "\n";
    } catch (int i) {
        std::cout << "int: " << i << "\n";
    } catch (...) {
        std::cout << "unknown\n";
    }
}
```

A. double: 42
B. int: 42
C. unknown
D. 编译错误

## Explanation

B


`throw 42` 抛出一个 `int` 类型的异常。C++ 异常匹配**不做隐式类型转换**（与函数调用不同），`catch (double)` 不能匹配 `int` 异常，因此跳过。`catch (int i)` 精确匹配，输出 `int: 42`。`catch (...)` 是兜底子句，只有前面所有子句都不匹配时才执行。
