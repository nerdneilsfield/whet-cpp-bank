---
qid: cpp-class-multi-003
type: multi
kp: [cpp-classes]
difficulty: medium
answer_key: [A, B]
---
关于 friend 访问规则，**哪些说法是正确的**？（多选）

A. friend 关系不能被继承（派生类不自动继承基类的 friend）。
B. friend 关系不是对称的（A friend B 不代表 B friend A）。
C. friend 函数是类的成员函数。
D. friend 声明可以放在类的 private 区或 public 区，访问权限不同。

---

**解析：**

A 正确：友元关系不可继承。
B 正确：友元关系单向，且不可传递。
C 错误：friend 函数是非成员函数，只是被授予访问类私有成员的权限。
D 错误：friend 声明放在 private 或 public 区效果完全相同，访问权限说明符不影响 friend 声明。