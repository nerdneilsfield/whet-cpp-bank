---
qid: cpp-build-031
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: B
---

# 下列 CMake 命令中，用于生成**可执行文件** `app`（由 `main.cpp` 和 `foo.cpp` 编译）的是？

A. `add_library(app main.cpp foo.cpp)`  
B. `add_executable(app main.cpp foo.cpp)`  
C. `target_sources(app main.cpp foo.cpp)`  
D. `build_executable(app main.cpp foo.cpp)`

## Explanation

正确答案是 B。`add_executable(app main.cpp foo.cpp)` 定义一个名为 `app` 的可执行目标，并指定其源文件。`add_library` 用于生成库，`target_sources` 是给已有目标追加源文件。
