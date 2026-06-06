---
qid: cpp-ptr-019
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: A
---

以下代码中，`p + 1` 实际移动了多少字节（假设 `int` 为 4 字节）？

```cpp
int arr[] = {1, 2, 3};
int* p = arr;
p = p + 1;
```

A. 4
B. 1
C. 8
D. 取决于平台
