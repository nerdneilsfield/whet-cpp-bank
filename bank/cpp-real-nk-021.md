---
qid: cpp-real-nk-021
type: single
kp: [cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: medium
answer_key: D
tags: [interview-real, alibaba]
---

```cpp
class Base { public: virtual void f() { std::cout << "B"; } };
class Derived : public Base { public: void f() override { std::cout << "D"; } };

Base* p = new Derived;
p->f();
```

调用 `p->f()` 时实际发生的步骤是：

A. 编译期决定调用 `Base::f`，输出 "B"
B. 运行时通过 RTTI 查 typeid 决定，调用 `Derived::f`，输出 "D"
C. 编译器看到 virtual 关键字，运行期通过名称查找符号表调用 `Derived::f`
D. 通过 `p` 找到对象首部的 **vptr**，从 vptr 指向的 **vtable** 中取第 0 项（即 `f` 的函数地址，已被 Derived 重写），间接调用 `Derived::f`，输出 "D"

---

**解析：**

多态的运行期实现机制（动态绑定）：

1. 编译期：编译器看到 `p->f()` 是 virtual 调用，生成查表代码（而不是直接 call）
2. 运行期：
   - `vptr = *(void**)p`（取对象首部的 vptr）
   - `func = vptr[index_of_f]`（vtable 的下标在编译期就确定了）
   - `(*func)(p)`（调用，p 作为 this）

`Derived::f` 的地址覆盖了 vtable 中 `Base::f` 的槽位，所以最终调用 Derived 版本。

性能开销：相比直接 call 多了一次内存访问（取 vptr）和一次间接调用，禁止内联。

不是 RTTI：RTTI（typeid/dynamic_cast）是另一套机制，虚函数调用不依赖 typeid。

**来源：** CSDN/阿里云 C++ 多态原理 / 《深度探索 C++ 对象模型》

## Explanation

正确答案是 D。
性能开销：相比直接 call 多了一次内存访问（取 vptr）和一次间接调用，禁止内联。
不是 RTTI：RTTI（typeid/dynamic_cast）是另一套机制，虚函数调用不依赖 typeid。
