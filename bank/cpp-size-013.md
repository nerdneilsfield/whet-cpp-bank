---
qid: cpp-size-013
type: fill
kp: [cpp-type-sizes]
difficulty: easy
answer_key: "std::nullptr_t"
---

`nullptr` 的类型是 _____（填写完整类型名称，包含命名空间）。

## 解析

填入 `std::nullptr_t`，因为题目要求的是该规则下的精确表达或标准名称。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
