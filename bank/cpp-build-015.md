---
qid: cpp-build-015
type: fill
kp: [cpp-build-tools]
difficulty: easy
answer_key: -fPIC
---

# 题目

编译共享库时，必须加上 **___** 选项，使生成的机器码中地址通过相对偏移表示，从而允许库被加载到内存任意位置而不需要重定位修正。

## 答案

`-fPIC`（Position-Independent Code，位置无关代码）。若忘记该选项，链接器在创建 `.so` 时会报错或运行时崩溃。
