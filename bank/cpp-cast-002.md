---
qid: cpp-cast-002
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: C
---

# dynamic_cast 失败行为

对指针使用 `dynamic_cast` 向下转型失败时，会发生什么？

A. 编译错误
B. 抛出 `std::bad_cast` 异常
C. 返回 `nullptr`
D. 返回未定义值

## 解析

正确答案为 C，因为“返回 `nullptr`”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
