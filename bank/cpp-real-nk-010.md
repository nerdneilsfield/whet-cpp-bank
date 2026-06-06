---
qid: cpp-real-nk-010
type: single
kp: [cpp-stl-basics]
primary_kp: cpp-stl-basics
difficulty: easy
answer_key: B
tags: [interview-real, nowcoder]
---

STL 的六大组件中，**不包括**下列哪一个？

A. 容器（Container）
B. 工厂（Factory）
C. 算法（Algorithm）
D. 配置器（Allocator）

---

**解析：**

STL 六大组件（侯捷《STL 源码剖析》经典分类）：

1. **容器（Containers）**：vector、list、map 等
2. **算法（Algorithms）**：sort、find、accumulate 等
3. **迭代器（Iterators）**：连接容器和算法的桥梁
4. **仿函数（Functors / Function Objects）**：重载 `operator()` 的类
5. **适配器（Adapters）**：stack/queue（容器适配器）、bind（函数适配器）、reverse_iterator（迭代器适配器）
6. **配置器（Allocators）**：内存管理

工厂（Factory）是设计模式概念，不属于 STL 组件分类。

也有"五大组件"的说法，将仿函数归入算法，但主流（侯捷书）是六大。

**来源：** 牛客网 C++ STL 高频面试题 / 《STL 源码剖析》侯捷