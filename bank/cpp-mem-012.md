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

## 解析

答案是 `nullptr`，`release()` 会放弃 `unique_ptr` 的所有权并返回原始指针，同时把内部保存的指针置空。之后资源不再由 `up` 自动释放，必须由调用者用合适方式手动释放，本题中用 `delete raw`。常见误区是把 `release()` 当成 `reset()`；`reset()` 会释放旧资源，而 `release()` 不会。
