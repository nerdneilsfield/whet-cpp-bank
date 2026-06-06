---
qid: cpp-real-nk-multi-007
type: multi
kp: [cpp-special-members, cpp-classes]
primary_kp: cpp-special-members
difficulty: hard
answer_key: [A, B, D]
tags: [interview-real, nowcoder]
---

C++ 中类的"五大特殊成员函数"（C++11 后）包括以下哪些？

A. **默认构造函数 `Foo()`**
B. **拷贝构造函数 `Foo(const Foo&)` 和拷贝赋值运算符 `operator=(const Foo&)`**
C. 友元函数
D. **移动构造函数 `Foo(Foo&&)` 和移动赋值运算符 `operator=(Foo&&)`，以及析构函数 `~Foo()`**

---

**解析：**

C++11 之前的"三大法则"（Rule of Three）：
1. 拷贝构造
2. 拷贝赋值
3. 析构函数

C++11 后扩展为"**五大法则**"（Rule of Five），增加：
4. 移动构造
5. 移动赋值

加上默认构造，共 6 个特殊成员函数：默认构造、析构、拷贝构造、拷贝赋值、移动构造、移动赋值。

**规则**：
- 如果你定义了其中一个（特别是析构函数），通常需要思考是否要定义其他几个
- 用户定义了拷贝/拷贝赋值/析构 → 编译器**不会**生成默认移动构造/赋值
- 用户定义了移动构造/移动赋值 → 编译器把拷贝构造/赋值**delete**

**Rule of Zero**：现代 C++ 推荐——通过使用智能指针和标准容器，让编译器为你生成所有特殊成员。

C 错：友元不是特殊成员函数，是访问控制机制。

**来源：** 牛客网 C++ 现代特性面试题 / Effective Modern C++ Item 17