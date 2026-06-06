---
qid: cpp-stl-adv-013
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: C
---

# s.compare() 的返回值语义

```cpp
#include <string>

std::string a = "apple";
std::string b = "banana";
int result = a.compare(b);
```

关于 `compare()` 的返回值，以下说法正确的是？

A. 返回 `true` 或 `false`
B. 返回值为 1、0 或 -1，含义固定
C. 返回 0 表示相等，负数表示调用者小于参数，正数表示调用者大于参数
D. `"apple".compare("banana")` 返回正数，因为 apple 字母更少

> **知识点**：`compare()` 按字典序比较，返回：0（相等）、负数（调用者 < 参数）、正数（调用者 > 参数）。具体值不保证是 -1/1，只保证符号。`'a' < 'b'`，所以 `"apple".compare("banana")` 返回负数。
