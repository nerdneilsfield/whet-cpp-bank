---
qid: cpp-ub-multi-hard-002
type: multi
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: [A, B, C]
---
关于对象生命周期（object lifetime），以下说法正确的是哪些？

```cpp
struct S { int x; ~S() { x = 0; } };
S* p = static_cast<S*>(std::aligned_alloc(alignof(S), sizeof(S)));
// (1) 已经分配存储但未构造，生命周期开始了吗？
p->x = 5;                          // (2)
std::construct_at(p, S{1});
std::destroy_at(p);
// (3) p->x 在析构后还有效吗？
```

A. (1) 中已分配存储但未调用构造函数，对象的生命周期尚未开始——此时 `p->x = 5` 是 UB（试图访问生命周期未开始的对象的成员）。
B. `reuse` 概念：`std::construct_at` 在已分配存储上创建新对象，旧对象不能在此地址上同时存在。
C. (3) 中 `std::destroy_at` 调用后对象的生命周期结束；但存储仍存在，只是对象已死；访问已销毁对象的非静态成员是 UB。
D. 若对象生命周期已结束但存储空间未被释放，可使用 `std::launder` 在任意情况下安全地读取对象的原始成员值。

---

**解析：**

A 正确：分配存储不等于对象存在。C++ 标准规定对象的生命周期从构造函数完成开始；在构造之前通过指针访问是 UB（[basic.life]/6）。
B 正确：`std::construct_at` 是 C++20 的"原地构造"原语，在已分配存储上开始新对象的生命周期；新旧对象的生命周期不能重叠。存储空间可被重用以构造新对象。
C 正确：析构后对象生命周期结束，访问其非静态成员（包括读取其内存）是 UB。很多开发者误认为"存储没释放就能读"，这是错的——对象的生命周期已结束。
D 错误：`std::launder` 不能凭空绕过生命周期规则。它解决的是"相同地址上已存在对象被 reinterpret_cast 为指向前对象的指针但不能访问其成员"的问题（pointer provenance / TBAA）。在对象生命周期已结束后依然不能通过 `std::launder` 恢复访问。