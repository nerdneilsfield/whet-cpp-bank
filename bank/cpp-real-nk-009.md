---
qid: cpp-real-nk-009
type: single
kp: [cpp-stl-basics]
primary_kp: cpp-stl-basics
difficulty: medium
answer_key: D
tags: [interview-real, nowcoder]
---

关于 C++ STL 配置器（Allocator），下列描述正确的是：

A. 配置器主要负责内存的分配和释放，与对象的构造/析构无关
B. 标准配置器 `std::allocator` 内部使用 `malloc/free` 实现
C. 所有 STL 容器都必须使用同一个类型的配置器
D. 配置器通过 `::operator new` 和 `::operator delete` 分配原始内存，再使用 `placement new` 构造对象

---

**解析：**

A **错**：STL 配置器设计将**内存分配**（`allocate`/`deallocate`）和**对象构造**（`construct`/`destroy`）分开。在 C++17 之前，配置器提供 `construct` 和 `destroy` 方法。

B **错**（细节）：标准实现（GCC libstdc++）默认通过 `::operator new` 分配内存（非直接 malloc）。SGI STL 早期版本确实用 malloc。

C **错**：容器可以在模板参数中指定配置器，不同容器可以用不同类型。

D **对**：是具体实现机制。`allocator::allocate` 调用 `::operator new` 获取原始内存，`allocator::construct` （C++20 前）使用 `placement new` 在内存上构造对象。C++20 起配置器的 `construct`/`destroy` 已被废弃（改用 `std::allocator_traits`）。

**来源：** 牛客网 C++ STL 高频面试题 / 《STL 源码剖析》侯捷