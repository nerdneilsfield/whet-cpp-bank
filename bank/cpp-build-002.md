---
qid: cpp-build-002
type: fill
kp: [cpp-build-tools]
difficulty: easy
answer_key: .i
---

# 题目

使用 `gcc -E foo.c -o foo.i` 命令后，输出文件 `foo.i` 是经过 **___** 阶段产生的中间文件，其内容是宏展开、头文件包含后的纯 C 源代码。

## 答案

预处理（Preprocessing）阶段产生的文件，扩展名为 `.i`。
