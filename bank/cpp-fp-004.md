---
qid: cpp-fp-004
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: D
---

# 认知：无捕获 lambda 与函数指针

关于无捕获 lambda 与函数指针的关系，下列说法正确的是？

A. 任何 lambda 都可以隐式转换为对应签名的函数指针  
B. 无捕获 lambda 不能转换为函数指针，必须用 `std::function`  
C. 只有标注 `[[nodiscard]]` 的 lambda 才能转换为函数指针  
D. 无捕获 lambda 可以隐式转换为签名匹配的函数指针，有捕获的则不行  
