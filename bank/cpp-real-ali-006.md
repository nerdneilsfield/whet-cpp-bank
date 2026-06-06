---
qid: cpp-real-ali-006
type: single
kp: [cpp-memory-mgmt, cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: hard
answer_key: A
tags: [interview-real, alibaba]
---
```cpp
class Base {
public:
    virtual void f() { std::cout << "Base"; }
    virtual ~Base() = default;
private:
    int a;
};
class Derived : public Base {
public:
    void f() override { std::cout << "Derived"; }
private:
    int b;
};
// 假设 sizeof(int) = 4, 无 padding 调整时
// 考虑虚表指针
```
sizeof(Base) 和 sizeof(Derived) 分别是多少？（假设 64 位系统，无特殊对齐）

A. 16, 16
B. 8, 8
C. 16, 24
D. 8, 16

---

**解析：**

选 A。关键在于**虚函数表指针（vptr）的大小和对齐**。

64 位系统：vptr = 8 字节，int = 4 字节。
- Base：vptr(8) + int(4) = 12，对齐到 8 的倍数 → **16 字节**
- Derived：继承 Base 的 vptr(8) + int a(4) + int b(4) = 16，已是 8 的倍数 → **16 字节**

**为什么 Derived 没有对齐到 24？** 因为 Derived 没有自己的 vptr，它复用 Base 的 vptr。多继承时才可能有多个 vptr。

内存布局（64位）：
```
Base:
[vptr (8)] [a (4)] [padding (4)]  → 16

Derived:
[vptr (8)] [a (4)] [b (4)]        → 16
```

对齐规则：所有成员对齐到自身大小倍数，结构体对齐到最大成员对齐值的倍数（vptr = 8）。

**来源：** 阿里 C++ 面试（参考：huihut/interview、cs-offer）