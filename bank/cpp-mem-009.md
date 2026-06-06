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

## 解析

应填写 `delete[] arr`，因为 `arr` 来自 `new int[100]`，释放形式必须匹配数组 new。写成 `delete arr` 会造成未定义行为，而只调用析构相关工具也不会释放底层内存。现代代码中更推荐用 `std::vector<int>` 或智能指针避免手写 `new[]/delete[]`。
