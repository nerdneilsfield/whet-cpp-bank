---
qid: cpp-ptr-m-004
type: multi
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: [A, B, D]
---

给定 `int arr[5];`，下列关于**数组名**的说法，哪些是正确的？（选择所有正确项）

A. 在大多数表达式中，`arr` 会退化为指向第一个元素的指针，即等价于 `&arr[0]`
B. `sizeof(arr)` 返回整个数组的字节大小（不发生退化）
C. `arr` 是一个指针变量，可以对其执行 `arr++`
D. 将 `arr` 传递给函数时，函数接收的是指针，无法在函数内用 `sizeof` 获取原数组大小
