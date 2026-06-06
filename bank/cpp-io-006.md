---
qid: cpp-io-006
type: single
kp: [cpp-io]
difficulty: easy
answer_key: C
---

# 认知：ios::trunc 效果

以 `ios::out | ios::trunc` 打开一个已存在的文件，结果是：

A. 文件打开失败，返回错误
B. 在文件末尾追加新内容
C. 文件原有内容被清空，从头写入
D. 以只读方式打开
