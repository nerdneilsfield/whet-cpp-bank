---
qid: cpp-smf-005
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: B
---

"Rule of 0" 的核心思想是什么？

A. 一个类最多只能定义 0 个特殊成员函数
B. 如果类不直接管理资源，则不应定义任何特殊成员函数，让编译器自动生成
C. 所有特殊成员函数都必须显式声明为 `= default`
D. 析构函数的函数体应保持为空

## Explanation

正确答案是 B，Rule of Zero 主张不直接管理裸资源的类不写特殊成员，让成员对象自己通过 RAII 管理资源。这样编译器生成的拷贝、移动和析构通常就是正确的。它不是要求机械地写零个函数，而是建议用 `vector`、`string`、智能指针等成员表达所有权。
