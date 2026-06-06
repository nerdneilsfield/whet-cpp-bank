---
qid: cpp-cast-hard-004
type: single
kp: [cpp-casting]
difficulty: hard
answer_key: B
---

下列代码的行为是？

```cpp
struct Base {};
struct Derived : Base { int extra; };

Base b;
Derived* pd = static_cast<Derived*>(&b);  // ①
pd->extra = 0;                            // ②
```

A. 合法：`static_cast` 总能成功
B. ① 编译通过（语法合法）但 ② 行为未定义：`&b` 实际指向 `Base` 对象，没有 `Derived` 子对象，访问 `extra` 是访问越界且违反对象类型规则
C. 编译错误：`static_cast` 不能向下转
D. `dynamic_cast` 在此返回 `nullptr` 同样保护

## Explanation

`static_cast` 在派生关系合法时允许向下转——但**不做运行时检查**。它只验证两个类型确实有继承关系（编译期），并返回调整后的指针。若指针实际指向的对象不是目标类型的实例，**得到的派生指针就是无效的**：访问派生类独有成员（如 `pd->extra`）属于访问不存在对象的内存，是未定义行为。

要做安全向下转应该用 `dynamic_cast`——但前提是基类多态（至少有一个虚函数），否则 `dynamic_cast` 编译失败。本题中 `Base` 无虚函数，`dynamic_cast` 不可用。这也提示一个设计准则：若打算多态层次，把基类设为多态（虚析构 + 虚函数）；否则别用基类指针指向派生对象。
