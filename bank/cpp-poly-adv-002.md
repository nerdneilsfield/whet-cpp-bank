---
qid: cpp-poly-adv-002
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: C
---

比较 CRTP 基类与含虚函数基类的 `sizeof`，在 64 位平台上下列说法**正确**的是？

```cpp
struct DataOnly { int x; };

template <typename D>
struct CRTPBase { int x; };

struct VirtualBase { virtual void f(); int x; };

struct CRTPChild : CRTPBase<CRTPChild> {};
struct VirtualChild : VirtualBase {};
```

A. `sizeof(CRTPChild) == sizeof(VirtualChild)`，两者均含 vptr
B. `sizeof(CRTPChild) > sizeof(VirtualChild)`，CRTP 需要额外存储类型信息
C. `sizeof(CRTPChild) < sizeof(VirtualChild)`，CRTP 无 vptr，VirtualChild 含 8 字节 vptr
D. 两者 `sizeof` 相同，因为编译器会对 CRTP 做同等优化

---

**解析：**

- `VirtualBase` 含虚函数，编译器在对象头部注入一个 **vptr（虚表指针）**，64 位下占 8 字节。因此 `sizeof(VirtualChild) = 8(vptr) + 4(int) + 4(padding) = 16`（或平台相关对齐结果，但必然包含 8 字节 vptr）。
- CRTP 是**静态多态**：`CRTPBase<D>` 是普通模板类，没有虚函数，不注入 vptr。`sizeof(CRTPChild) = sizeof(int) = 4`（加对齐可能是 4）。
- 因此 `sizeof(CRTPChild) < sizeof(VirtualChild)`，CRTP 的内存优势源于消除了 vptr。
