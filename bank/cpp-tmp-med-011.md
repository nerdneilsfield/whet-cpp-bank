---
qid: cpp-tmp-med-011
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: B
---

标签分派（Tag Dispatch）的核心机制是？

A. 在运行期检查类型信息（RTTI），调用对应函数
B. 定义空 struct 作为 tag 类型，通过函数重载在编译期选择实现
C. 使用 `#ifdef` 宏在编译期切换代码路径
D. 依赖虚函数表在运行期分派调用

---

**解析：**

Tag dispatch 的做法：  
1. 定义若干**空 struct** 作为 tag（如 `struct true_type{}; struct false_type{};`）。  
2. 辅助函数根据某个 trait（如 `std::is_integral<T>`）构造对应 tag 实例并传入重载函数。  
3. 编译器在编译期根据 tag 类型选择正确的重载，生成不同代码路径。

全程无运行期开销，无虚函数，无 RTTI。这是 C++11 之前实现编译期条件分派的主要手段。

## Explanation

正确答案是 B，即 定义空 struct 作为 tag 类型，通过函数重载在编译期选择实现。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
