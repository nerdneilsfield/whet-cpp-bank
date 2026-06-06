---
qid: cpp-io-r-002
type: fill
kp: [cpp-io]
difficulty: easy
answer_key: "Hello, 42!"
---

## 题目

阅读以下代码，`result` 的值是什么？

```cpp
#include <sstream>
#include <string>
#include <iostream>

int main() {
    std::ostringstream oss;
    oss << "Hello, " << 42 << "!";
    std::string result = oss.str();
    std::cout << result << std::endl;
}
```

`result` = ___

## 解析

`std::ostringstream` 像普通流一样拼接输出：先写入字符串 `"Hello, "`，再写入整数 `42`（自动转为字符串），再写入 `"!"`。调用 `.str()` 返回缓冲区内容，即 `"Hello, 42!"`。
