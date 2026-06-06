---
qid: cpp-ns-004
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: A
---

下列关于 `#define` 对象宏的说法，正确的是？

```cpp
#define MAX_SIZE 100
```

A. 预处理阶段将源码中所有 `MAX_SIZE` 文本替换为 `100`，不做类型检查
B. 编译器会为 `MAX_SIZE` 分配一块存储空间
C. `MAX_SIZE` 具有 `int` 类型，可以用 `sizeof(MAX_SIZE)` 得到 4
D. 该宏只在定义它的函数内有效
