---
qid: cpp-class-m-006
type: multi
kp: [cpp-classes]
difficulty: easy
answer_key: [A, B, C]
---

关于 C++ 中的 `this` 指针，下列哪些说法**正确**？（选择所有正确项）

A. `this` 是一个指向当前对象的指针，类型为 `ClassName*`（在 `const` 成员函数中为 `const ClassName*`）
B. `this` 指针可以用于在成员函数中区分同名的成员变量与局部变量，例如 `this->x = x;`
C. 成员函数可以通过 `return *this;` 返回当前对象的引用，从而支持链式调用
D. 静态成员函数也有 `this` 指针，但它指向类本身而非某个对象

## 解析

正确答案为 A、B、C。A项“`this` 是一个指向当前对象的指针，类型为 `ClassName*`（在 `const` 成员函数中为 `const ClassName*`）”是正确项；B项“`this` 指针可以用于在成员函数中区分同名的成员变量与局部变量，例如 `this->x = x;`”是正确项；C项“成员函数可以通过 `return *this;` 返回当前对象的引用，从而支持链式调用”是正确项；D项“静态成员函数也有 `this` 指针，但它指向类本身而非某个对象”不是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
