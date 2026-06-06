---
qid: cpp-ub-011
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# use-after-free

```cpp
int* p = new int(42);
delete p;
int v = *p;   // 此行
```

标注行的行为是：

A. `v` 为 0，`delete` 会清零内存
B. 未定义行为（use-after-free），内存可能已被重用
C. 编译错误，`delete` 后指针变为 `nullptr`，不可解引用
D. 确定崩溃（段错误），属于可预测的运行时错误，不是 UB
