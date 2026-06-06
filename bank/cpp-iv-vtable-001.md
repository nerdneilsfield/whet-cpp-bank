---
qid: cpp-iv-vtable-001
type: short
kp: [cpp-interview]
difficulty: medium
tags: [腾讯, 阿里, 小红书]
rubric:
  - 能说清 vtable 是编译器生成的静态函数指针数组
  - 知道每个多态类（而非对象）对应一张 vtable
  - 能描述 vtable 的内存布局（RTTI 指针 + 虚函数指针序列）
  - 知道对象通过 vptr 指向所属类的 vtable
  - 能画出单继承场景下对象/vtable 的内存关系图
---

# 虚函数表（vtable）是什么？内存布局如何？

### 问题

请解释 C++ 虚函数表（vtable）的概念：它是什么、由谁生成、存储在哪里？并描述单继承场景下对象和 vtable 的内存布局。

## Explanation

### 什么是 vtable

vtable（virtual table，虚函数表）是编译器为**每一个含有虚函数的类**生成的一张静态函数指针数组。它是实现运行时多态的核心数据结构——调用虚函数时，程序在运行时通过查表决定调用哪个具体实现，而非编译期静态绑定。

关键点：
- vtable 属于**类**，不属于对象；同一个类的所有对象共享同一张表。
- vtable 由编译器自动生成，通常存放在只读数据段（`.rodata`）。
- 每个含虚函数的对象头部有一个隐藏的 **vptr**（虚指针），指向所属类的 vtable。

### 内存布局

以 GCC/Clang（Itanium ABI）为例，单继承场景：

```
vtable for Derived
┌─────────────────────────────────────┐
│ offset_to_top (0 for primary base)  │  ← 用于多继承调整 this 指针
│ RTTI pointer (type_info*)           │  ← typeid / dynamic_cast 使用
│ ptr → Derived::vfunc0              │  ← 第 0 个虚函数
│ ptr → Derived::vfunc1              │  ← 第 1 个虚函数
│ ...                                 │
└─────────────────────────────────────┘

Object layout (Derived d)
┌─────────────────────────────────────┐
│ vptr  ──────────────────────────────┼──→ 指向 Derived vtable 中第一个函数指针
│ (Base members)                      │
│ (Derived members)                   │
└─────────────────────────────────────┘
```

代码验证（仅供演示，真实项目不要这样做）：

```cpp
#include <iostream>
struct Base {
    virtual void foo() { std::cout << "Base::foo\n"; }
    virtual void bar() { std::cout << "Base::bar\n"; }
};
struct Derived : Base {
    void foo() override { std::cout << "Derived::foo\n"; }
};

int main() {
    Derived d;
    // vptr 在对象头部，取出指向 vtable 的指针
    void** vtable = *reinterpret_cast<void***>(&d);
    // 调用第 0 个槽（foo）
    reinterpret_cast<void(*)()>(vtable[0])(); // 输出 Derived::foo
    // 调用第 1 个槽（bar，未覆盖，仍是 Base::bar）
    reinterpret_cast<void(*)()>(vtable[1])(); // 输出 Base::bar
}
```

### 常见追问

- **vtable 何时构建？** 程序加载时（编译期生成，链接期合并到只读段）。
- **vtable 会增加对象大小吗？** 不直接增加表本身大小，但每个对象多一个 `vptr`（通常 8 字节）。
- **非多态类有 vtable 吗？** 没有；没有虚函数的类不生成 vtable，对象也不含 vptr。
