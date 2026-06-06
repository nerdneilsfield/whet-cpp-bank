---
qid: cpp-ns-006
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: D
---

以下代码中，`hello()` 会被调用吗？

```cpp
#define DEBUG 0

#ifdef DEBUG
    hello();
#endif
```

A. 会，因为 `DEBUG` 已经被定义
B. 不会，因为 `DEBUG` 的值为 0（假）
C. 编译报错，`#ifdef` 不能检测值为 0 的宏
D. 会，`#ifdef` 只检查宏是否被定义，不看值；但此处 `DEBUG` 确实已定义，所以 `hello()` 会被编译进去
