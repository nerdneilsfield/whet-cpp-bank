---
qid: cpp-build-012
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: A
---

# 题目

程序中调用了 `sin()`、`sqrt()` 等数学函数，链接时提示"undefined reference to `sin`"。需要在编译命令末尾加上哪个选项？

A. `-lm`
B. `-lmath`
C. `-Lm`
D. `-Im`

## 选项解析

- A：正确。数学库的文件名是 `libm.so`，对应链接选项 `-lm`。
- B：库文件不叫 `libmath.so`，该选项无效。
- C：`-L` 是路径，`-Lm` 意为在名为 `m` 的目录中搜索库，与题意无关。
- D：`-I` 是头文件路径，`-Im` 无意义。

## 解析

正确答案为 A，因为“`-lm`”符合题干所问的 C++ 规则或代码执行结果。B、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。构建题要区分预处理、编译、汇编、链接以及编译选项、库路径和目标文件的职责。
