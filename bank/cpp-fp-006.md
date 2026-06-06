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

## 解析

正确答案是 B，对应“可以存储函数指针、lambda（含捕获）、函数对象、std::bind 结果等任意签名匹配的可调用对象”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“只能存储普通函数指针”不满足题干要求；C 项“只能存储无捕获的 lambda”不满足题干要求；D 项“只能存储成员函数指针”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
