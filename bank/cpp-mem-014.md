---
qid: cpp-mem-014
type: fill
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "false（或 0）"
---

# 阅读代码，回答问题

```cpp
#include <memory>
#include <iostream>

int main() {
    auto sp = std::make_shared<int>(42);
    std::weak_ptr<int> wp = sp;

    sp.reset();   // 释放 shared_ptr

    std::cout << std::boolalpha << !wp.expired(); // 输出什么？
}
```

`!wp.expired()` 的输出是 ______。

<!--
sp.reset() 后引用计数降为 0，对象被销毁，wp.expired() 返回 true，
取反后输出 false。答案：false
-->
