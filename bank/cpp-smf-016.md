---
qid: cpp-smf-016
type: multi
kp: [cpp-special-members]
difficulty: easy
answer_key: [A, C, D]
---

以下哪些情况会导致编译器**不**自动生成移动构造函数？（多选）

A. 用户显式定义了析构函数
B. 用户将默认构造函数标记为 `= default`
C. 用户显式定义了拷贝构造函数
D. 用户显式定义了拷贝赋值运算符
E. 类中所有数据成员均为内置类型（int、double 等）
