---
qid: cpp-stl-adv-010
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: B
---

# s.replace() 替换子串

```cpp
#include <string>
#include <iostream>

int main() {
    std::string s = "I like cats";
    s.replace(7, 4, "dogs");
    std::cout << s << std::endl;
    return 0;
}
```

上述代码输出什么？

A. `I like cats dogs`
B. `I like dogs`
C. `I like dogscats`
D. `I like cat`

> **知识点**：`replace(pos, len, str)` 将从 `pos` 开始的 `len` 个字符替换为 `str`，并修改原字符串。`"I like cats"` 中下标 7 是 `'c'`，`len=4` 覆盖 `"cats"`，替换为 `"dogs"`，结果为 `"I like dogs"`。
