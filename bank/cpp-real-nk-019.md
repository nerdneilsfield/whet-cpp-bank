---
qid: cpp-real-nk-019
type: single
kp: [cpp-polymorphism, cpp-classes]
primary_kp: cpp-polymorphism
difficulty: medium
answer_key: B
tags: [interview-real, nowcoder]
---

虚函数表指针（vptr）放在对象内存的什么位置？

A. 对象内存的**末尾**（保证向后兼容 C struct 布局）
B. 对象内存的**最前面**（GCC/MSVC 默认实现）
C. 对象内存的**中间**位置
D. 不存放在对象内存中，由编译器注册到全局表中

---

**解析：**

ABI 规范（Itanium C++ ABI，被 GCC/Clang 采用；MSVC 类似）规定：

- vptr 放在对象内存的**起始位置**（偏移 0）
- 这样通过对象地址可以直接获得 vptr，查找虚函数时只需要一次间接寻址：`*(address_of_object) → vtable → operator[] → function address`

例外情况：
1. **多继承**：每个包含虚函数的基类子对象都有自己的 vptr，分布在对象的不同偏移位置
2. **虚继承**：存在额外的 vtt（Virtual Table Table）机制
3. **ABI 未强制**：理论上编译器可以放在任何位置，但主流都放前面

验证：`std::cout << sizeof(Base);` 在没有其他成员时返回指针大小（64 位为 8），这变相说明 vptr 加在对象起始。

**来源：** CSDN C++ 虚函数详解 / Itanium C++ ABI §2.5

## Explanation

正确答案是 B。
关键是说明正确选项成立的 C++ 规则，以及其他选项忽略的边界条件。
常见误区是只记结论，不解释代码行为、编译行为或复杂度前提。
