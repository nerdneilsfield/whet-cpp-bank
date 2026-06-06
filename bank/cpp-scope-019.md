---
qid: cpp-scope-019
type: multi
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: [B, C]
---

# 内部链接的实现方式

下列哪些方法能使一个文件作用域的标识符具有**内部链接**？（多选）

A. `extern int x = 5;`
B. `static int x = 5;`
C. `namespace { int x = 5; }`
D. `inline int x = 5;`

## Explanation

正确答案是 B, C。B 项 ``static int x = 5;`` 符合规则；C 项 ``namespace { int x = 5; }`` 符合规则；A 项 ``extern int x = 5;`` 不满足该规则；D 项 ``inline int x = 5;`` 不满足该规则。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 多选题常见误区是只看关键字相似就勾选，而没有逐项检查它是否真的满足题干条件。
