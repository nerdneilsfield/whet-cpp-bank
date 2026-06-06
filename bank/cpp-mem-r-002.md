---
qid: cpp-mem-r-002
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "C"
---

## 题目

阅读以下代码，`use_count` 的三次输出依次是什么？

```cpp
#include <memory>
#include <iostream>

int main() {
    auto a = std::make_shared<int>(10);
    std::cout << a.use_count() << "\n";   // (1)

    auto b = a;
    std::cout << a.use_count() << "\n";   // (2)

    b.reset();
    std::cout << a.use_count() << "\n";   // (3)
}
```

A. `1 1 1`
B. `1 2 2`
C. `1 2 1`
D. `2 2 1`

## 解析

`make_shared` 创建对象后只有 `a` 持有，引用计数为 1；`b = a` 拷贝共享所有权，计数升至 2；`b.reset()` 释放 `b` 的持有，计数降回 1。三次输出为 `1 2 1`。
