---
qid: cpp-smf-007
type: fill
kp: [cpp-special-members]
difficulty: easy
answer_key: "移动构造函数、移动赋值运算符"
---

"Rule of 5" 在 Rule of 3 基础上额外要求显式定义 ______。（填写两个特殊成员函数名称）

## Explanation

答案是移动构造函数和移动赋值运算符。Rule of Five 是 C++11 移动语义后对 Rule of Three 的扩展：直接管理资源的类除了拷贝控制和析构，还要定义移动控制。否则 `std::move` 可能退化为拷贝，或者默认移动产生资源重复释放风险。
