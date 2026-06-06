---
qid: cpp-iv-vtable-002
type: short
kp: [cpp-interview]
difficulty: medium
tags: [字节跳动, 华为]
rubric:
  - 知道 vptr 通常位于对象内存的起始位置（Itanium ABI）
  - 能说明 vptr 由构造函数负责初始化，且分阶段设置
  - 理解基类构造期间 vptr 指向基类 vtable，派生类构造后才指向派生类 vtable
  - 知道 vptr 初始化顺序与构造函数调用顺序一致
  - 能解释这对"构造期间调用虚函数"的影响
---

# vptr 在对象内存中的位置？构造时何时设置？

## 问题

vptr（虚指针）在对象内存中处于什么位置？它是在什么时候、由谁来设置的？在构造过程中，vptr 的值会发生变化吗？

## 参考答案

### vptr 的位置

在主流 ABI（GCC/Clang 的 Itanium ABI、MSVC）下，**vptr 位于对象内存的最起始处**（偏移量 0）。这样做的好处是：通过对象指针取 `*ptr` 即可直接得到 vtable 地址，无需额外偏移计算，调用效率最高。

```
Derived 对象内存（单继承）
┌──────────────────────────────┐  ← &d（地址 0x...）
│  vptr  (8 bytes)             │  ← 偏移 0，指向 Derived::vtable
│  Base::member_a (4 bytes)    │
│  Base::member_b (4 bytes)    │
│  Derived::member_c (8 bytes) │
└──────────────────────────────┘
```

### vptr 由构造函数负责设置

vptr **不是程序员写的代码**设置的，而是编译器在每个构造函数的**函数序言（prologue）**中自动插入赋值指令，在任何用户代码执行之前完成。

**关键：vptr 随构造函数的调用层次分阶段更新。**

```cpp
struct Base {
    Base() {
        // 编译器在此处插入：vptr = &Base::vtable
        // 此时 vptr 指向 Base 的 vtable
    }
    virtual void who() { std::cout << "Base\n"; }
};

struct Derived : Base {
    Derived() : Base() {
        // Base() 返回后，编译器插入：vptr = &Derived::vtable
        // 此后 vptr 才指向 Derived 的 vtable
    }
    void who() override { std::cout << "Derived\n"; }
};
```

构造顺序与 vptr 变化：

| 阶段 | 正在执行 | vptr 指向 |
|------|---------|-----------|
| 1 | `Base::Base()` 函数体 | `Base` 的 vtable |
| 2 | `Derived::Derived()` 函数体 | `Derived` 的 vtable |

### 实际影响

因为构造期间 vptr 尚未完成最终设置，**在基类构造函数中调用虚函数不会分派到派生类**（见 vtable-006 题）。

析构时顺序相反：进入 `Derived::~Derived()` 时 vptr 仍指向 Derived vtable；执行完毕后编译器将 vptr 重置回 Base vtable，再调用 `Base::~Base()`。这保证析构期间调用的虚函数也只解析到"当前析构层级"的版本。

```cpp
Derived d; // 构造：vptr: Base → Derived
           // 析构：vptr: Derived → Base（反向）
```

### 常见追问

- **vptr 赋值是线程安全的吗？** 构造函数本身不是线程安全的，多线程共享未构造完的对象是 UB。
- **MSVC 和 GCC 的 vptr 位置一样吗？** 单继承时都在偏移 0；多继承时可能存在多个 vptr，位置不同（见 vtable-003 题）。
