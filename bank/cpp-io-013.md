---
qid: cpp-io-013
type: fill
kp: [cpp-io]
difficulty: easy
answer_key: "score=99"
---

# 代码阅读：ostringstream 拼接

```cpp
#include <sstream>
std::ostringstream oss;
oss << "score=" << 99;
std::cout << oss.str();
```

程序输出是 ______。

## 解析

应填写 `score=99`。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
