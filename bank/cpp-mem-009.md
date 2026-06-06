---
qid: cpp-mem-009
type: fill
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "delete[] arr"
---

# 代码补全：释放数组

```cpp
int* arr = new int[100];
// ... 使用 arr ...
______;   // 正确释放数组内存
```

在横线处填入正确的释放语句。

<!--
new[] 对应 delete[]。答案：delete[] arr
-->
