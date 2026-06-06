---
qid: cpp-ub-009
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: A
---

# 数组越界写入

```cpp
int arr[3] = {1, 2, 3};
arr[3] = 99;   // 下标 3，数组大小为 3
```

上述代码的行为是：

A. 未定义行为，可能损坏相邻内存
B. 编译错误，越界访问在编译期检测
C. 运行时必然抛出异常
D. 合法：C++ 数组允许写入"结束哨兵"位置
