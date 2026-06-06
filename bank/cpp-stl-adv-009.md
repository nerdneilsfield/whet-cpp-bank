---
qid: cpp-stl-adv-009
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: C
---

# s.substr(pos, len) 用法与越界行为

```cpp
#include <string>

std::string s = "Hello, World!";
std::string sub = s.substr(7, 5);
```

关于 `s.substr(pos, len)`，以下哪条描述正确？

A. `sub` 的值为 `"Hello"`
B. `substr` 修改原字符串 `s`，截断为前 `len` 个字符
C. `sub` 的值为 `"World"`，若 `pos` 超过字符串长度则抛出 `std::out_of_range`
D. `len` 超出剩余长度时抛出异常

> **知识点**：`substr(pos, len)` 返回从 `pos` 起最多 `len` 个字符的新字符串，不修改原串。下标 7 对应 `'W'`，取 5 个字符得 `"World"`。`pos` 超界抛 `std::out_of_range`；`len` 超出剩余长度则安全截断至字符串末尾（不抛异常）。
