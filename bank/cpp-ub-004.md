---
qid: cpp-ub-004
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: A
---

# 悬空指针属于哪类问题

函数返回局部变量的地址，调用方使用该地址访问数据，这是：

A. 未定义行为（悬空指针解引用）
B. 编译错误，无法通过编译
C. 运行时会抛出异常，属于可预测的崩溃
D. 合法操作，局部变量在栈上，地址有效
