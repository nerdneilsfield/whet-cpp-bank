---
qid: cpp-real-multi-004
type: multi
kp: [cpp-exceptions, cpp-move-semantics]
primary_kp: cpp-exceptions
difficulty: hard
answer_key: [A, B, D]
tags: [interview-real, multi-vendor]
---
```cpp
void f1() noexcept;              // 承诺不抛
void f2() noexcept(true);        // 等价 f1
void f3() noexcept(false);       // 可能抛
void f4() noexcept(noexcept(g()));   // 条件 noexcept
```
关于 `noexcept` 关键字，以下说法**正确**的是（多选）：

A. noexcept 函数若实际抛出异常，会调用 std::terminate（不会做栈展开）
B. 移动构造函数应该标记 noexcept，否则 std::vector 扩容时会退化为拷贝
C. 析构函数在 C++11 起默认是 noexcept，即使函数体内有可能抛异常的代码
D. noexcept 是函数签名的一部分（声明和定义需一致），但**不是**重载的区分依据
E. noexcept(true) 比 noexcept(false) 函数执行速度快 10 倍

---

**解析：**

正确答案：**A、B、D**。

**A 正确：** noexcept 函数抛出异常 → 直接 `std::terminate()`。注意**不做栈展开**（实现允许做或不做），与 throw() 行为相同。

**B 正确：** 这是 C++11 的关键设计——`std::move_if_noexcept` 在 vector 扩容时检查移动构造是否 noexcept，若不 noexcept 退化为拷贝（保证强异常安全）。

**C 正确（但本题选项 D 优先）：** C++11 起，**析构函数默认是 noexcept**（除非基类析构是 noexcept(false) 或成员析构非 noexcept）。这与历史 C++ 不同。

实际选项辨析：C 描述部分正确（"默认 noexcept"对），但"即使函数体内有可能抛异常"这一部分有误导——如果函数体内有非 noexcept 的调用，析构本身仍标记 noexcept，但运行时一旦抛出会 terminate。这一选项有歧义。**取严格正确的 A、B、D。**

**D 正确：** noexcept 是函数签名的一部分（C++17 起），声明和定义必须一致。但**不能用 noexcept 重载函数**（不能同时定义 `void f() noexcept` 和 `void f()`）。它影响函数指针类型：`void(*p)() noexcept` 不能指向 noexcept(false) 函数。

**E 错误：** noexcept 不直接提升运行时性能，主要是**让编译器和库进行优化决策**（如 move_if_noexcept、不生成异常表代码）。具体效果因实现而异。

**来源：** 跨厂 C++ noexcept 深入考点（参考：cppreference、Effective Modern C++ Item 14、ISO C++ N4659）

## Explanation

正确答案：A、B、D。
A 正确： noexcept 函数抛出异常 → 直接 std::terminate()；B 正确： 这是 C++11 的关键设计——std::move_if_noexcept 在 vector 扩容时检查移动构造是否 noexcept，若不 noexcept 退化为拷贝（保证强异常安全）。
C 正确（但本题选项 D 优先）： C++11 起，析构函数默认是 noexcept（除非基类析构是 noexcept(false) 或成员析构非 noexcept）。
注意不做栈展开（实现允许做或不做），与 throw() 行为相同。
