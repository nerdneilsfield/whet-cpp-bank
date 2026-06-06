---
qid: cpp-stl-adv-011
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: A
---

# s.erase() 删除子串

```cpp
#include <string>
#include <iostream>

int main() {
    std::string s = "Hello, World!";
    s.erase(5, 7);
    std::cout << s << std::endl;
    return 0;
}
```

上述代码输出什么？

A. `Hello!`
B. `Hello, World!`（`erase` 返回新串，不修改原串）
C. `Hello World!`
D. `Helloorld!`

> **知识点**：`erase(pos, len)` 直接修改原字符串，删除从 `pos` 起的 `len` 个字符。`"Hello, World!"` 中下标 5 是 `','`，删除 7 个字符（`, World`），剩余 `"Hello!"`。注意：`erase` 是原地操作，不是返回新字符串。
