---
qid: cpp-scope-med-001
type: single
kp: [cpp-scope-linkage]
difficulty: medium
answer_key: D
---

C++ 中 `static` 关键字在不同上下文中的含义不同。以下哪条表述**正确**？

A. 在命名空间作用域声明 `static int x;` 表示 x 是线程局部存储
B. 在类内声明 `static int x;` 表示 x 是类的成员，每个对象拥有独立副本
C. 在命名空间作用域声明 `static int x;` 和匿名命名空间 `namespace { int x; }` 完全等价，包括 C++17 的行为
D. 在命名空间作用域，`static` 赋予内部链接（internal linkage）；在类内，`static` 声明类的静态成员，所有对象共享

---

**解析：**

`static` 关键字的多义性：

- **命名空间作用域**（文件作用域）：`static int x;` → 内部链接，该变量仅在当前翻译单元可见。C++11 起**不推荐**使用，建议用匿名命名空间 `namespace { int x; }`。但两者不完全等价：匿名命名空间中的类型名在 ODR 规则下更安全。
- **类作用域**：`static int x;` → 类的静态成员，不占用对象空间，所有对象共享一个实例，必须在类外单独定义（C++17 起用 `inline static` 可在类内定义）。
- **局部作用域**：`static int x;` → 静态局部变量，首次调用时初始化，函数返回后保持值。

A 错在说线程局部存储（那是 `thread_local`）；B 错在说"每个对象拥有独立副本"；C 错在说"完全等价"。