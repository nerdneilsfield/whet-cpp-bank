---
qid: cpp-ub-007
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# 空指针解引用

```cpp
int* p = nullptr;
int v = *p;
```

上述代码的行为是：

A. 编译错误，`nullptr` 不能被解引用
B. 未定义行为，结果不可预测
C. 确定崩溃（Segfault），属于可预测的运行时错误，不是 UB
D. `v` 被初始化为 0，因为 `nullptr` 地址为 0
