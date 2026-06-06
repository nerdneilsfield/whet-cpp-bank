---
qid: cpp-real-en-015
type: single
kp: [cpp-classes, cpp-inheritance]
primary_kp: cpp-classes
difficulty: medium
answer_key: B
tags: [interview-real, interviewbit]
---
在面向对象设计中，composition（组合）、aggregation（聚合）和 inheritance（继承）三者最本质的区别是？

A. 三者概念完全相同，只是语法不同
B. Composition 表示"整体-部分"强拥有关系（生命周期绑定），Aggregation 表示"整体-部分"弱拥有关系（生命周期独立），Inheritance 表示"is-a"关系
C. Inheritance 比 Composition 更灵活，应优先使用 Inheritance
D. Aggregation 表示"is-a"关系，Inheritance 表示"has-a"关系

---

**解析：**

三种关系：
- **Composition（组合）**："has-a"强关系。部分对象的生命周期由整体管理，整体销毁时部分也随之销毁。如 `Car` 包含 `Engine`（引擎在车内创建和销毁）。用成员变量实现。
- **Aggregation（聚合）**："has-a"弱关系。部分对象可以独立于整体存在。如 `Car` 包含 `Wheel`（轮子可以换）。用指针/引用成员实现。
- **Inheritance（继承）**："is-a"关系。派生类是基类的一种。如 `Car` 继承 `Vehicle`。

设计原则：优先使用组合/聚合而非继承（"favor composition over inheritance"），因为继承破坏封装、耦合度高。

**来源：** InterviewBit "C++ Interview Questions" — Composition vs Aggregation vs Inheritance

## Explanation

正确答案是 B。
三种关系： Composition（组合）："has-a"强关系；部分对象的生命周期由整体管理，整体销毁时部分也随之销毁。
如 Car 包含 Engine（引擎在车内创建和销毁）；用成员变量实现。
