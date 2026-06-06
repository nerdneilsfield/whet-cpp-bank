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

## Explanation

应填 `int`。`std::variant` 在若干备选类型中持有一个当前值，访问类型不匹配会失败或抛异常。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
