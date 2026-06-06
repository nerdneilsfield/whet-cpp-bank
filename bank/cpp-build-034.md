---
qid: cpp-build-034
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: A
---

# 在 CMake 中，`find_package(OpenCV REQUIRED)` 的作用是？

A. 在系统中查找 OpenCV 库，找不到则报错终止配置  
B. 自动下载并安装 OpenCV  
C. 将 OpenCV 源码添加到当前构建系统  
D. 查找 OpenCV，找不到时发出警告但继续构建

## Explanation

正确答案为 A，因为“在系统中查找 OpenCV 库，找不到则报错终止配置”符合题干所问的 C++ 规则或代码执行结果。B、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。构建题要区分预处理、编译、汇编、链接以及编译选项、库路径和目标文件的职责。
