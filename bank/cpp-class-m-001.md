---
qid: cpp-class-m-001
type: multi
kp: [cpp-classes]
difficulty: easy
answer_key: [A, C]
---

关于 C++ 中 `class` 与 `struct` 的区别与联系，下列哪些说法**正确**？（选择所有正确项）

A. `struct` 的成员默认访问权限为 `public`，`class` 的成员默认访问权限为 `private`
B. `struct` 不能有构造函数和析构函数，`class` 可以
C. `struct` 和 `class` 都支持继承，且继承默认访问权限也不同：`struct` 默认 `public` 继承，`class` 默认 `private` 继承
D. `struct` 不能包含成员函数，只能包含数据成员

## 解析

正确答案为 A、C。A项“`struct` 的成员默认访问权限为 `public`，`class` 的成员默认访问权限为 `private`”是正确项；B项“`struct` 不能有构造函数和析构函数，`class` 可以”不是正确项；C项“`struct` 和 `class` 都支持继承，且继承默认访问权限也不同：`struct` 默认 `public` 继承，`class` 默认 `private` 继承”是正确项；D项“`struct` 不能包含成员函数，只能包含数据成员”不是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
