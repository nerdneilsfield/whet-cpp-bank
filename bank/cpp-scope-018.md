---
qid: cpp-scope-018
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: A
---

# extern const 使常量具有外部链接

下列代码能让其他翻译单元访问 `MAX` 常量的**正确**做法是？

A.
```cpp
// header.h
extern const int MAX;

// defs.cpp
extern const int MAX = 100;
```

B.
```cpp
// header.h
const int MAX = 100;
```

C.
```cpp
// defs.cpp
static const int MAX = 100;
```

D.
```cpp
// defs.cpp
namespace { const int MAX = 100; }
```

选项中哪个能使 `MAX` 被多个翻译单元共享？

答：______
