---
qid: cpp-cpp11-019
type: multi
kp: [cpp-cpp11]
difficulty: easy
answer_key: [B, C]
---

# 代码阅读：enum class 的正确用法

以下哪些代码片段能**通过编译**？（多选）

```cpp
enum class Dir { North, South, East, West };
```

A.
```cpp
int d = Dir::North;
```

B.
```cpp
Dir d = Dir::North;
```

C.
```cpp
if (Dir::North == Dir::North) {}
```

D.
```cpp
int d = North;  // 无作用域限定
```
