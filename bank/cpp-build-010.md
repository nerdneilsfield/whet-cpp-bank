---
qid: cpp-build-010
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: C
---

# 题目

项目头文件放在 `./include` 目录中，编译时应使用哪个选项告知编译器在该目录搜索头文件？

A. `-L./include`
B. `-l./include`
C. `-I./include`
D. `-D./include`

## 选项解析

- A：`-L` 用于添加**库**的搜索路径，不影响头文件查找。
- B：`-l` 用于指定链接的**库名**，如 `-lm`。
- C：正确。`-I<dir>` 将指定目录添加到头文件搜索路径列表。
- D：`-D` 用于预定义宏，与路径无关。
