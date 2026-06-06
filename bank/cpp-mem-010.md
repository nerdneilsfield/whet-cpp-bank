---
qid: cpp-mem-010
type: fill
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "std::make_unique<int>(42)"
---

# 代码补全：创建 unique_ptr（C++14）

```cpp
#include <memory>

auto p = ______;   // 创建一个持有 int(42) 的 unique_ptr
```

使用推荐的工厂函数（C++14 引入）填写横线。

<!--
答案：std::make_unique<int>(42)
-->
