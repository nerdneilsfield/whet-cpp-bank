---
qid: cpp-ptr-m-005
type: multi
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: [A, C, D]
---

给定 `int arr[5] = {10, 20, 30, 40, 50}; int* p = arr;`，下列关于**指针算术**的说法，哪些是正确的？（选择所有正确项）

A. `p + 2` 指向 `arr[2]`，即值为 `30` 的元素
B. `p + 2` 将指针向后移动 2 字节（与 `int` 大小无关）
C. `*(p + 1)` 与 `p[1]` 等价，均为 `20`
D. 两个指向同一数组元素的指针相减，结果表示它们之间相差的元素个数
