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

## Explanation

答案是 `2`，`sp1`、`sp2`、`sp3` 初始都共享同一个控制块，计数为 3。`sp3.reset()` 释放 `sp3` 的所有权后，只剩 `sp1` 和 `sp2` 两个强引用。`use_count()` 统计的是同一控制块的强引用数量，不包含已经 reset 的空指针。
