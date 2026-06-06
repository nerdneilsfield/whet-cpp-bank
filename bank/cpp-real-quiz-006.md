---
qid: cpp-real-quiz-006
type: single
kp: [cpp-types]
primary_kp: cpp-types
difficulty: medium
answer_key: A
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的输出是？

```cpp
#include <iostream>
int main() {
    bool b = true;
    int i = b + b + b;
    std::cout << i << ' ' << (true == 1) << ' ' << (false == 0);
}
```

A. `3 1 1`
B. `1 1 1`
C. `3 true true`
D. 实现定义

---

**解析：**

[conv.prom]/6：`bool` 的整型提升把 `true` 提升为 `1`，`false` 提升为 `0`，这是**标准固定**而非实现定义。所以 `b + b + b = 1 + 1 + 1 = 3`。

`(true == 1)` 中 `true` 被提升为 `int(1)`，与 `1` 相等，结果为 `bool(true)`，`<<` 默认按整数 `1` 输出。`(false == 0)` 同理输出 `1`。

注意 `std::cout << b` 默认输出 `0`/`1`，除非用 `std::boolalpha`。

**来源：** cppquiz.org（多题考点）；C++17 [conv.prom]/6

## Explanation

正确答案是 A。
[conv.prom]/6：bool 的整型提升把 true 提升为 1，false 提升为 0，这是标准固定而非实现定义；所以 b + b + b = 1 + 1 + 1 = 3。
(true == 1) 中 true 被提升为 int(1)，与 1 相等，结果为 bool(true)，<< 默认按整数 1 输出；(false == 0) 同理输出 1。
注意 std::cout << b 默认输出 0/1，除非用 std::boolalpha。
