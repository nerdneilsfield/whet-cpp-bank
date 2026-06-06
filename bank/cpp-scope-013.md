---
qid: cpp-scope-013
type: fill
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: "链接错误（linker error）"
---

# 跨编译单元重复定义

有两个源文件：

```cpp
// a.cpp
int value = 5;

// b.cpp
int value = 10;
```

将 `a.cpp` 和 `b.cpp` 一起编译链接时，会产生什么错误？

答：______ （填"编译错误"、"链接错误"或"运行时错误"）
