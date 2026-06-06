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
