---
qid: cpp-io-r-001
type: single
kp: [cpp-io]
difficulty: easy
answer_key: "B"
---

### 题目

阅读以下代码，程序实际读取到 `line` 的内容是什么？

```cpp
#include <iostream>
#include <string>

int main() {
    int n;
    std::string line;
    std::cin >> n;
    std::getline(std::cin, line);
    std::cout << "[" << line << "]" << std::endl;
}
```

输入为：
```
42
hello world
```

A. `[hello world]`
B. `[]`
C. `[42]`
D. 程序挂起，等待更多输入

## Explanation

`std::cin >> n` 读取整数 `42` 后，输入缓冲区中还残留换行符 `\n`。紧随其后的 `std::getline` 立即读到该换行符就返回，`line` 为空字符串，输出 `[]`。修复方法是在两者之间插入 `std::cin.ignore()`。
