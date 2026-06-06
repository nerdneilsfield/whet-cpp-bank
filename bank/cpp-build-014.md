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

## 选项解析

- A：`-static` 生成静态可执行文件，与共享库无关。
- B：正确。`-fPIC` 生成位置无关代码（共享库必须），`-shared` 告知链接器输出共享库而非可执行文件。
- C：`-c` 只编译到目标文件，不链接，无法单独生成共享库。
- D：`-g` 只加调试信息，不影响输出类型。
