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

## Explanation

正确答案为 A、B。A项“friend 关系不能被继承（派生类不自动继承基类的 friend）。”是正确项；B项“friend 关系不是对称的（A friend B 不代表 B friend A）。”是正确项；C项“friend 函数是类的成员函数。”不是正确项；D项“friend 声明可以放在类的 private 区或 public 区，访问权限不同。”不是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
