---
qid: cpp-mem-011
type: fill
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "2"
---

# 阅读代码，回答问题

```cpp
#include <memory>
#include <iostream>

int main() {
    auto sp1 = std::make_shared<int>(100);
    auto sp2 = sp1;               // 拷贝
    auto sp3 = sp1;               // 再拷贝

    sp3.reset();                  // 释放 sp3 的所有权

    std::cout << sp1.use_count(); // 输出什么？
}
```

`sp1.use_count()` 的输出是 ______。

<!--
sp1、sp2 持有同一对象；sp3.reset() 后引用计数从 3 降为 2。答案：2
-->
