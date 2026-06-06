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

## 解析

正确答案是 C，因为该选项对应 ``sizeof(CRTPChild) < sizeof(VirtualChild)`，CRTP 无 vptr，VirtualChild 含 8 字节 vptr`，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
