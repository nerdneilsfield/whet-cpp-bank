---
qid: cpp-cross-me-002
type: single
kp: [cpp-memory-mgmt, cpp-exceptions]
difficulty: easy
answer_key: C
---

# 题目

```cpp
#include <iostream>
#include <memory>
#include <stdexcept>

struct Node {};

int main() {
    auto sp = std::make_shared<Node>();
    std::cout << sp.use_count() << "\n";   // line A

    try {
        auto sp2 = sp;
        std::cout << sp.use_count() << "\n"; // line B
        throw std::runtime_error("err");
    } catch (...) {
        std::cout << sp.use_count() << "\n"; // line C
    }

    std::cout << sp.use_count() << "\n";     // line D
}
```

程序的输出是？

A. 1 / 2 / 2 / 1

B. 1 / 2 / 0 / 1

C. 1 / 2 / 1 / 1

D. 1 / 1 / 1 / 1

---

## Explanation

- **line A**：只有 `sp`，引用计数 = 1。
- **line B**：`sp2` 是 `sp` 的副本，引用计数 = 2。
- 异常抛出，`try` 块栈展开，`sp2` 被销毁，引用计数降回 1。
- **line C**（catch 块内）：`sp` 仍然存活，引用计数 = 1。
- **line D**：catch 结束，`sp` 仍存活，引用计数 = 1。

选 **C**：1 / 2 / 1 / 1。`shared_ptr` 异常安全——栈展开时拷贝的 `sp2` 会被正确销毁，不会泄漏。
