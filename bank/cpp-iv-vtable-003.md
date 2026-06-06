---
qid: cpp-iv-vtable-003
type: short
kp: [cpp-interview]
difficulty: medium
tags: [Google, 阿里]
rubric:
  - 知道多重继承时派生类通常有多个 vptr（每个直接基类对应一个）
  - 能解释 thunk（调整器）的作用——调整 this 指针到正确的子对象
  - 理解 primary base 和 secondary base 的概念
  - 能说出为什么需要多个 vtable（不同基类接口需要独立的函数指针表）
  - 菱形继承（虚继承）场景下的额外复杂性可加分说明
---

# 多重继承时虚函数表如何组织？Derived 有几个 vptr？

### 问题

假设 `class Derived : public Base1, public Base2`，且 `Base1` 和 `Base2` 都有虚函数。请描述 `Derived` 对象的内存布局，vtable 是如何组织的，共有几个 vptr？

## Explanation

### 基本规则

在 Itanium ABI 下，**派生类拥有与其直接多态基类数量相同的 vptr**（每个独立基类子对象一个）。对于 `Derived : Base1, Base2`，`Derived` 对象含有 **2 个 vptr**。

### 内存布局

```
Derived d 的对象内存布局
┌─────────────────────────────────────┐  ← &d，也是 Base1 子对象起始
│  vptr1  ────────────────────────────┼──→ Derived-in-Base1 vtable
│  Base1::data                        │
├─────────────────────────────────────┤  ← &d 的 Base2 子对象（有偏移）
│  vptr2  ────────────────────────────┼──→ Derived-in-Base2 vtable
│  Base2::data                        │
├─────────────────────────────────────┤
│  Derived::data                      │
└─────────────────────────────────────┘
```

### 为什么需要两张 vtable？

当通过 `Base2*` 指针调用虚函数时，`this` 必须指向 `Base2` 子对象（偏移非零）。但 `Derived` 的实现函数接受的 `this` 是整个 `Derived` 对象的地址。因此需要一个 **thunk（调整器）**：先将 `this` 调整回 `Derived` 起始地址，再跳转到真正的实现函数。

```cpp
struct Base1 { virtual void f(); int a; };
struct Base2 { virtual void g(); int b; };
struct Derived : Base1, Base2 {
    void f() override;  // 覆盖 Base1::f
    void g() override;  // 覆盖 Base2::g
};

Derived d;
Base2* p2 = &d;        // p2 指向 d 内的 Base2 子对象，有偏移
p2->g();               // 经 vptr2 查表，找到 thunk，thunk 调整 this → 调用 Derived::g
```

### 两张 vtable 的内容示意

```
vtable for Derived（Base1 视角，primary）
│ offset_to_top = 0
│ RTTI
│ → Derived::f        ← 直接跳转，this 已是 Derived*
│ → Base1::x（未覆盖）

vtable for Derived（Base2 视角，secondary）
│ offset_to_top = -sizeof(Base1-part)   ← 负数，用于 this 回调
│ RTTI
│ → thunk for Derived::g               ← 先减偏移，再调用 Derived::g
```

### 虚继承（菱形）的额外复杂性

```cpp
struct A { virtual void h(); };
struct B : virtual A {};
struct C : virtual A {};
struct D : B, C {};  // A 只有一份
```

此时编译器引入 **virtual base table（vbtable）** 或在 vtable 中追加虚基类偏移字段，vptr 数量和布局更复杂（MSVC 与 GCC 实现差异较大）。面试若追问到这里，能说出"虚基类共享一份子对象，需要运行时查偏移"即可。

### 常见追问

- **`dynamic_cast` 如何跨 Base2* → Derived* 转换？** 通过 RTTI 和 offset_to_top 完成。
- **多个 vptr 会增加多少开销？** 每个额外 vptr 占 8 字节（64 位），且构造时需逐一初始化。
