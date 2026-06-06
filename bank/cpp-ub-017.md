---
qid: cpp-ub-017
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# double-free

```cpp
int* p = new int(5);
delete p;
delete p;   // 第二次 delete
```

第二次 `delete p` 的行为是：

A. 安全，`delete` 对同一指针的第二次调用被标准允许且为空操作
B. 未定义行为（double-free），可能破坏堆结构或被利用作安全漏洞
C. 编译错误，编译器追踪所有权并拒绝二次释放
D. 运行时必然崩溃，但不是未定义行为

## Explanation

正确答案是 B，即 未定义行为（double-free），可能破坏堆结构或被利用作安全漏洞。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
