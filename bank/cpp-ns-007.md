---
qid: cpp-ns-007
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: B
---

以下 `#if / #elif / #else` 代码最终打印什么？

```cpp
#define LEVEL 2

#if LEVEL == 1
    std::cout << "one";
#elif LEVEL == 2
    std::cout << "two";
#else
    std::cout << "other";
#endif
```

A. `one`
B. `two`
C. `other`
D. 编译错误
