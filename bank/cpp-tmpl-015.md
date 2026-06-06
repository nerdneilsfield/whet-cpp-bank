---
qid: cpp-tmpl-015
type: multi
kp: [cpp-templates]
difficulty: easy
answer_key: [A, C, D]
---

# 类模板特征

关于类模板，下列说法正确的有哪些？（多选）

A. `std::vector<int>` 和 `std::vector<double>` 是两个不同的类型
B. 类模板的成员函数不能再是函数模板
C. 类模板可以有非类型模板参数，如 `template<typename T, int N>`
D. 类模板的定义通常放在头文件中
E. 类模板实例化时，所有成员函数都会被编译，即使未被调用

## Explanation

正确选项是 A（`std::vector<int>` 和 `std::vector<double>` 是两个不同的类型）、C（类模板可以有非类型模板参数，如 `template<typename T, int N>`）、D（类模板的定义通常放在头文件中），它们符合本题涉及的 C++ 规则。B（类模板的成员函数不能再是函数模板） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
