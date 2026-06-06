---
qid: cpp-exc-016
type: fill
kp: [cpp-exceptions]
difficulty: easy
answer_key: "disk full"
---

# C++ 异常处理：代码阅读——what() 输出

```cpp
#include <iostream>
#include <stdexcept>
int main() {
    try {
        throw std::runtime_error("disk full");
    } catch (std::exception& e) {
        std::cout << e.what() << "\n";
    }
}
```

程序输出的内容是 ______（填运行时打印的字符串）。

> 提示：`what()` 返回构造时传入的消息字符串。

答：______

## 解析

应填 `disk full`。`throw` 表达式用于抛出异常；在 `catch` 中单独写 `throw;` 表示重新抛出当前异常。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
