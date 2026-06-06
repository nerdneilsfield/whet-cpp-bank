---
qid: cpp-scope-012
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: B
---

# 编译错误识别：重复定义

下列代码在**同一个翻译单元**中会发生什么？

```cpp
// file.cpp
int value = 5;
int value = 10;  // 第二行
```

A. 合法，后一个定义覆盖前一个
B. 编译错误，ODR 禁止同一翻译单元内重复定义同名变量
C. 合法，但运行时行为未定义
D. 链接错误，而非编译错误
