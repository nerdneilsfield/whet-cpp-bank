---
qid: cpp-build-035
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: C
---

# CMake 推荐的 out-of-source 构建流程（在项目根目录下）依次是？

A. `make` → `cmake ..`  
B. `cmake .` → `make`  
C. `mkdir build && cd build` → `cmake ..` → `make`  
D. `cmake --build` → `cmake --install`

## 解析

正确答案是 C。out-of-source 构建把构建产物放在单独的 `build/` 目录中，避免污染源码树。典型流程是创建并进入 `build`，运行 `cmake ..` 生成构建系统，再执行 `make` 或 `cmake --build .`。
