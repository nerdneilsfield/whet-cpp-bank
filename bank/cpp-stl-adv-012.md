---
qid: cpp-stl-adv-012
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: D
---

# s.insert() 在指定位置插入字符串

```cpp
#include <string>
#include <iostream>

int main() {
    std::string s = "Hello!";
    s.insert(5, ", World");
    std::cout << s << std::endl;
    return 0;
}
```

上述代码输出什么？

A. `Hello, World`
B. `, WorldHello!`
C. `Hello, World`（感叹号丢失）
D. `Hello, World!`

> **知识点**：`insert(pos, str)` 在下标 `pos` 处插入字符串 `str`，原下标 `pos` 及之后的字符向后移动。`"Hello!"` 下标 5 是 `'!'`，在它之前插入 `", World"`，结果为 `"Hello, World!"`。
