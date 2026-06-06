---
qid: cpp-io-r-005
type: fill
kp: [cpp-io]
difficulty: easy
answer_key: "3 6 9"
---

## 题目

阅读以下代码，输出结果是什么？

```cpp
#include <sstream>
#include <iostream>

int main() {
    std::string data = "3 6 9";
    std::istringstream iss(data);
    int a, b, c;
    iss >> a >> b >> c;
    std::cout << a << " " << b << " " << c << std::endl;
}
```

输出为：___

## 解析

`std::istringstream` 将字符串 `"3 6 9"` 视为输入流，`>>` 运算符按空格分隔依次解析整数：`a = 3`，`b = 6`，`c = 9`。最终输出 `3 6 9`。这是将字符串解析为结构化数据的常用惯用法，无需 `stoi` 或手动 `split`。
