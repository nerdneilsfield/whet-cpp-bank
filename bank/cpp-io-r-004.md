---
qid: cpp-io-r-004
type: single
kp: [cpp-io]
difficulty: easy
answer_key: "B"
---

## 题目

阅读以下代码，输出结果是什么？

```cpp
#include <iostream>
#include <iomanip>

int main() {
    std::cout << std::setw(6) << 1 << 2 << 3 << std::endl;
}
```

A. `     1     2     3`
B. `     123`
C. `1     2     3`
D. `     1 2 3`

## 解析

`std::setw(n)` 是**非粘性（non-sticky）**操纵符：它只对紧随其后的**一个**输出操作有效，之后自动重置为 0。因此只有 `1` 被宽度为 6 的字段格式化（右对齐，填充 5 个空格），`2` 和 `3` 直接输出不带宽度，最终为 `     123`。
