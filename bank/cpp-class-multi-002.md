---
qid: cpp-class-multi-002
type: multi
kp: [cpp-classes]
difficulty: medium
answer_key: [A, C]
---
关于 C++17 中聚合（aggregate）初始化的要求，**哪些说法是正确的**？（多选）

A. 聚合类不能有用户提供（user-provided）的构造函数。
B. 聚合类不能有任何 public 基类。
C. C++17 起，聚合可以有 public 基类（允许聚合派生）。
D. 聚合类不能含有 private 或 protected 的非静态数据成员。

---

**解析：**

A 正确：聚合的定义要求没有用户声明/提供的构造函数（C++20 改为「用户声明」）。
B 错误：C++17 已放宽，允许有 public 基类。
C 正确：C++17 起聚合可有 public 非虚基类，可在花括号中初始化基类子对象。
D 正确：聚合不能含有 private/protected 的非 static 数据成员。

## 解析

正确答案为 A、C。A项“聚合类不能有用户提供（user-provided）的构造函数。”是正确项；B项“聚合类不能有任何 public 基类。”不是正确项；C项“C++17 起，聚合可以有 public 基类（允许聚合派生）。”是正确项；D项“聚合类不能含有 private 或 protected 的非静态数据成员。”不是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
