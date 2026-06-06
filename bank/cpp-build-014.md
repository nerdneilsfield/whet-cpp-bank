---
qid: cpp-build-014
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: B
---

# 题目

要将 `util.cpp` 编译成可被其他程序动态加载的共享库 `libutil.so`，需要用到以下哪两个选项的组合？

A. `-static` 和 `-o`
B. `-fPIC` 和 `-shared`
C. `-c` 和 `-shared`
D. `-g` 和 `-shared`

## Explanation

- A：`-static` 生成静态可执行文件，与共享库无关。
- B：正确。`-fPIC` 生成位置无关代码（共享库必须），`-shared` 告知链接器输出共享库而非可执行文件。
- C：`-c` 只编译到目标文件，不链接，无法单独生成共享库。
- D：`-g` 只加调试信息，不影响输出类型。


正确答案为 B，因为“`-fPIC` 和 `-shared`”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。构建题要区分预处理、编译、汇编、链接以及编译选项、库路径和目标文件的职责。
