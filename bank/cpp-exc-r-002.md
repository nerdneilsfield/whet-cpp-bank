---
qid: cpp-exc-r-002
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: B
---

## 题目

下面代码的输出是什么？

```cpp
#include <iostream>
#include <stdexcept>

struct Base : std::exception {};
struct Derived : Base {};

int main() {
    try {
        throw Derived{};
    } catch (Base& e) {
        std::cout << "Base\n";
    } catch (Derived& e) {
        std::cout << "Derived\n";
    }
}
```

A. 输出 `Derived`
B. 输出 `Base`
C. 两个 `catch` 都执行，输出 `Base` 和 `Derived`
D. 编译错误

## 答案

B

## 解析

`catch` 子句按**书写顺序**逐一匹配，第一个匹配的子句被执行后，后续子句不再检查。`Derived` 继承自 `Base`，`catch (Base&)` 能匹配 `Derived` 对象，因此第一个 `catch` 先匹配成功，输出 `Base`，`catch (Derived&)` 永远不会被执行。正确做法是把派生类 `catch` 写在基类之前。
