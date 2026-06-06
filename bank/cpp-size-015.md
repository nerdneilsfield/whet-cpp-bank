---
qid: cpp-size-015
type: fill
kp: [cpp-type-sizes]
difficulty: easy
answer_key: "指针大小（sizeof(void*)）"
---

`nullptr` 的类型 `std::nullptr_t` 的大小（`sizeof(std::nullptr_t)`）等于 _____（用文字描述，不填具体数字）。

## 解析

填入 `指针大小（sizeof(void*)）`，因为题目要求的是该规则下的精确表达或标准名称。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
