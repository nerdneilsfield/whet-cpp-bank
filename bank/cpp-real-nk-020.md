---
qid: cpp-real-nk-020
type: single
kp: [cpp-polymorphism, cpp-inheritance]
primary_kp: cpp-polymorphism
difficulty: hard
answer_key: C
tags: [interview-real, nowcoder]
---

```cpp
struct A { virtual void f(); int a; };
struct B { virtual void g(); int b; };
struct C : A, B { void f() override; void g() override; int c; };
```

关于 `C` 的内存布局，下列正确的是：

A. C 只有一个 vptr，指向 C 的虚函数表
B. C 有一个 vptr，C 的 vtable 同时包含 A 和 B 的虚函数槽位
C. **C 有两个 vptr**，分别对应 A 子对象和 B 子对象；调用 `B::g` 时通过 B 子对象的 vptr 查表，可能需要 **thunk** 调整 this 指针
D. C 不需要 vptr，多继承时虚函数调用通过动态查找符号表实现

---

**解析：**

多继承下，每个有虚函数的基类子对象都有**独立的 vptr 和 vtable**：

布局（典型）：
```
+--------+ ← 对象起始
| vptrA  |  ← A 子对象的 vptr
| a      |
+--------+
| vptrB  |  ← B 子对象的 vptr（偏移 = sizeof(A)）
| b      |
+--------+
| c      |
+--------+
```

**Thunk 调整**：当 `B* pb = &c; pb->g();` 调用时，需要把 `pb`（指向 B 子对象）通过 thunk 调整为指向 C 完整对象的指针，再调用 `C::g`。Thunk 是一段小代码，主要做 this 指针 offset 调整。

`dynamic_cast<C*>(pb)` 也是基于这种布局实现，通过 vtable 中保存的 type_info 和 offset 信息查找。

**来源：** 网易/阿里 C++ 面试题 / Itanium C++ ABI §2.5.2 / 《深度探索 C++ 对象模型》

## Explanation

正确答案是 C。
多继承下，每个有虚函数的基类子对象都有独立的 vptr 和 vtable： 布局（典型）： *Thunk 调整：当 B* pb = &c; pb->g(); 调用时，需要把 pb（指向 B 子对象）通过 thunk 调整为指向 C 完整对象的指针，再调用 C::g。Thunk 是一段小代码，主要做 this 指针 offset 调整。
dynamic_cast<C*>(pb) 也是基于这种布局实现，通过 vtable 中保存的 type_info 和 offset 信息查找。
