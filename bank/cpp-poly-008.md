---
qid: cpp-poly-008
type: fill
kp: [cpp-polymorphism]
difficulty: easy
answer_key: "vtable（虚函数表）"
---

# 填空题

C++ 实现运行时多态的底层机制是为每个含虚函数的类维护一张 ______，对象中有一个隐藏指针（vptr）指向它，函数调用时通过该指针查找实际实现。
