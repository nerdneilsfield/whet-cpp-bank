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

## Explanation

正确答案是 D，对应“无捕获 lambda 可以隐式转换为签名匹配的函数指针，有捕获的则不行”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“任何 lambda 都可以隐式转换为对应签名的函数指针”不满足题干要求；B 项“无捕获 lambda 不能转换为函数指针，必须用 std::function”不满足题干要求；C 项“只有标注 [[nodiscard]] 的 lambda 才能转换为函数指针”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
