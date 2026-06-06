---
qid: cpp-fp-006
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: B
---

# 认知：`std::function` 的用途

`std::function<int(int, int)>` 可以存储哪些可调用对象？

A. 只能存储普通函数指针  
B. 可以存储函数指针、lambda（含捕获）、函数对象、`std::bind` 结果等任意签名匹配的可调用对象  
C. 只能存储无捕获的 lambda  
D. 只能存储成员函数指针  
