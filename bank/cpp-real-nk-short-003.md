---
qid: cpp-real-nk-short-003
type: short
kp: [cpp-polymorphism, cpp-classes]
primary_kp: cpp-polymorphism
difficulty: hard
tags: [interview-real, alibaba]
rubric:
  - vtable 编译期建立（1 分）
  - vtable 位于只读段（1 分）
  - vptr 在对象首部（1 分）
  - vptr 在构造函数中初始化（1 分）
  - 多继承多个 vptr + thunk（2 分）
  - 构造/析构中虚函数调用规则（2 分）
---

请详细说明 C++ 虚函数（virtual function）的实现机制，包括：
1. vtable 在何时何地建立、放在哪里
2. vptr 何时初始化、放在对象什么位置
3. 单继承、多继承下 vtable 布局的差异
4. 构造/析构函数中调用虚函数的实际行为及原因

---

**解析（参考答案）：**

**1. vtable 的建立和位置**

- **建立时间**：编译期（编译器解析每个多态类时即生成 vtable 的布局）
- **存放位置**：通常在程序的只读数据段（`.rodata`）
- **每个类一张表**：所有同类对象共享同一张 vtable
- **内容**：函数指针数组，每个槽位对应一个虚函数（按声明顺序）；vtable 头部还包含 type_info 指针（用于 RTTI）和偏移量（用于多继承调整）

**2. vptr 的初始化和位置**

- **位置**：对象内存的**最开头**（偏移 0），Itanium C++ ABI 规定
- **初始化时机**：在构造函数中（具体是构造函数体执行**之前**），编译器自动注入代码：`this->__vptr = &TypeVtable;`
- **派生类构造**：先调用基类构造（设 vptr 指向基类 vtable），再设 vptr 指向派生类 vtable

**3. 单继承 vs 多继承的 vtable 布局**

**单继承**：
- 对象只有一个 vptr
- 派生类 vtable 复制基类布局，重写的虚函数覆盖对应槽位，新增的追加在末尾

**多继承**：
- 每个有虚函数的基类子对象都有自己的 vptr 和 vtable
- 对象布局：`[vptrA][A 成员][vptrB][B 成员][C 自身成员]`
- **Thunk**：通过 B* 调用被 C 重写的函数时，函数地址执行前需要把 this 指针调整回 C 对象起始位置（偏移调整）

**虚继承**：还有额外的 vtt（virtual table table）和 vbase offset 机制。

**4. 构造/析构中调用虚函数**

```cpp
class Base {
public:
    Base() { f(); }  // 调用 Base::f，不是派生类
    virtual void f() { std::cout << "Base"; }
    virtual ~Base() { f(); }  // 同样调用 Base::f
};

class Derived : public Base {
public:
    void f() override { std::cout << "Derived"; }
};

Derived d;  // 输出 "Base" 然后 "Base"（析构时）
```

**原因**：
- 构造期间，派生类部分还未构造，vptr 仍指向基类的 vtable
- 析构期间，派生类部分已先析构，vptr 已被改回基类 vtable
- 这是为了保证：调用虚函数时，对应的对象部分已经构造好

**结论**：永远不要在构造函数和析构函数中调用虚函数（动态绑定）。如果必须，明确写 `Base::f()` 表达意图。

**rubric:**
- vtable 编译期建立（1 分）
- vtable 位于只读段（1 分）
- vptr 在对象首部（1 分）
- vptr 在构造函数中初始化（1 分）
- 多继承多个 vptr + thunk（2 分）
- 构造/析构中虚函数调用规则（2 分）
- 解释为什么（vptr 状态）（2 分）

**来源：** 阿里 / 网易 C++ 多态机制面试题 / 《深度探索 C++ 对象模型》Lippman