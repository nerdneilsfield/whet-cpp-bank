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

## Explanation

正确答案是 B。`catch(...)` 是兜底处理器，可匹配任意类型的异常。选项 B 的表述“｀other｀（｀double｀ 不匹配 ｀int｀，落入 ｀catch(...)｀）”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
