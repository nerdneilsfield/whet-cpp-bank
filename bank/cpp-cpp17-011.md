---
qid: cpp-cpp17-011
type: fill
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "int"
---

# 代码阅读：std::variant 持有类型判断

```cpp
#include <variant>
#include <iostream>
#include <string>

int main() {
    std::variant<int, double, std::string> v = 42;
    if (std::holds_alternative<int>(v)) {
        std::cout << "int\n";
    } else if (std::holds_alternative<double>(v)) {
        std::cout << "double\n";
    } else {
        std::cout << "string\n";
    }
}
```

程序输出：`_______`

（填写完整输出，不含换行符）
