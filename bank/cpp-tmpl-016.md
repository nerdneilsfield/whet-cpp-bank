---
qid: cpp-tmpl-016
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

# 模板实例化时机

```cpp
// a.h
template<typename T>
T identity(T x) { return x; }

// a.cpp
#include "a.h"

// b.cpp
// #include "a.h" 未包含

int main() {
    int r = identity(42); // 此处调用
}
```

若 `b.cpp` 未包含 `a.h`，`main` 中调用 `identity(42)` 的结果是？

A. 正常编译，模板已在 `a.cpp` 中实例化
B. 编译错误，`identity` 未声明
C. 链接错误，找不到 `identity<int>` 的定义
D. 运行时错误
