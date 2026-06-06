---
qid: cpp-build-032
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: D
---

# 在 CMake 中，`add_library(mylib STATIC lib.cpp)` 与 `add_library(mylib SHARED lib.cpp)` 的区别是？

A. STATIC 生成可执行文件，SHARED 生成静态库  
B. STATIC 用于 Windows，SHARED 用于 Linux  
C. STATIC 编译更快，SHARED 占用内存更少（无其他区别）  
D. STATIC 生成 `.a`/`.lib` 静态库，SHARED 生成 `.so`/`.dll` 动态共享库

## Explanation

正确答案是 D。`STATIC` 生成静态库，Linux 常见后缀为 `.a`，Windows 常见为 `.lib`；`SHARED` 生成动态/共享库，常见后缀为 `.so`、`.dll` 或 `.dylib`。二者的链接方式和运行时部署方式不同。
