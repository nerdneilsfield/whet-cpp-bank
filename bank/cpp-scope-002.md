---
qid: cpp-scope-002
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: C
---

# static 全局变量的链接性

用 `static` 修饰的全局变量具有哪种链接性？

A. 外部链接（external linkage）
B. 无链接（no linkage）
C. 内部链接（internal linkage）
D. 动态链接（dynamic linkage）

## 解析

正确答案是 C，因为该选项对应 `内部链接（internal linkage）`，符合题中代码或概念的 C++ 语义。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
