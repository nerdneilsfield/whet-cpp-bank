---
qid: cpp-size-030
type: fill
kp: [cpp-type-sizes]
difficulty: easy
answer_key: "大端（big-endian）"
---

网络字节序（network byte order）采用的是___序，即低地址存放数据的高字节。

## 解析

填入 `大端（big-endian）`，因为题目要求的是该规则下的精确表达或标准名称。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
