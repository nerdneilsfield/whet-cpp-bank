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

应填写 `Hello, 42!`。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
