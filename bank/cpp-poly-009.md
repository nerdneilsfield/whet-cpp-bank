---
qid: cpp-poly-009
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: B
---

# 关于 vtable 的开销，以下哪项描述最准确？

A. 每个对象都会额外存储一张完整的 vtable，开销很大  
B. vtable 是每个类共享一张表，每个对象只多一个 vptr（通常 8 字节），开销很小  
C. 使用 `virtual` 函数没有任何运行时开销  
D. vtable 只在调试模式下存在，Release 编译会移除
