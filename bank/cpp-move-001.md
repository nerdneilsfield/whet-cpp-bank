---
qid: cpp-move-001
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: B
---

# lvalue 与 rvalue 的本质区别

下列关于 lvalue 和 rvalue 最准确的描述是？

A. lvalue 存储在栈上，rvalue 存储在堆上
B. lvalue 有名字（可寻址），rvalue 是临时的无名表达式
C. lvalue 只能出现在赋值号左边，rvalue 只能出现在右边
D. lvalue 是整数类型，rvalue 是浮点类型

## 解析

正确答案是 B，左值通常表示有身份、可取地址、可在表达式之后继续使用的对象；右值通常表示临时结果或将亡值。A 把值类别和存储位置混为一谈，栈/堆不是判断标准。C 也是过时简化，很多左值不能放在赋值号左边（如 const 左值），右值也可能出现在不同语法位置。
