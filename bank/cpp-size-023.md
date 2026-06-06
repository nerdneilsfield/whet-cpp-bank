---
qid: cpp-size-023
type: fill
kp: [cpp-type-sizes]
difficulty: easy
answer_key: "0xFF（或 0xFFFFFFFF，取决于 int 宽度；32 位 int 下为 0xFFFFFFFF）"
---

在补码表示中，-1 的所有位均为 1。对于 32 位 `int`，-1 的十六进制表示是 ___。

## Explanation

填入 `0xFF（或 0xFFFFFFFF，取决于 int 宽度；32 位 int 下为 0xFFFFFFFF）`，因为题目要求的是该规则下的精确表达或标准名称。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
