---
qid: cpp-mem-012
type: fill
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "nullptr"
---

# 阅读代码，回答问题

```cpp
#include <memory>
#include <iostream>

int main() {
    auto up = std::make_unique<int>(7);
    int* raw = up.release();   // release() 之后 up 管理什么？

    std::cout << (up.get() == nullptr ? "nullptr" : "non-null");
    delete raw;
}
```

`up.get()` 在 `release()` 之后返回 ______。

<!--
release() 放弃所有权，将内部指针置为 nullptr 并返回原始指针。答案：nullptr
-->
