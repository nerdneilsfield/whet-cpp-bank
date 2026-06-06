---
qid: cpp-exc-014
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: B
---

# C++ 异常处理：代码阅读——重新抛出

```cpp
#include <iostream>
#include <stdexcept>
void handle() {
    try {
        throw std::runtime_error("original");
    } catch (std::exception& e) {
        std::cout << "inner: " << e.what() << "\n";
        throw;  // 重新抛出
    }
}
int main() {
    try {
        handle();
    } catch (std::exception& e) {
        std::cout << "outer: " << e.what() << "\n";
    }
}
```

输出是？

A. 只有 `outer: original`
B. `inner: original` 然后 `outer: original`
C. `inner: original`，然后程序终止
D. `outer: original` 然后 `inner: original`

## Explanation

正确答案是 B。`throw` 表达式用于抛出异常；在 `catch` 中单独写 `throw;` 表示重新抛出当前异常。选项 B 的表述“｀inner: original｀ 然后 ｀outer: original｀”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
