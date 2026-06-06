---
qid: cpp-cast-005
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: B
---

# dynamic_cast 前提条件

使用 `dynamic_cast` 的必要条件是？

A. 基类有 `virtual` 析构函数，且继承为 private
B. 基类至少有一个 `virtual` 函数（即多态类型）
C. 编译时开启 `-O2` 优化
D. 派生类重写了基类的所有虚函数

## Explanation

正确答案为 B，因为“基类至少有一个 `virtual` 函数（即多态类型）”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
