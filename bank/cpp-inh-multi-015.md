---
qid: cpp-inh-multi-015
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

```cpp
struct A { int x; };
struct B : virtual public A {};   // 含 vptr
struct NV_B : public A {};        // 不含虚继承
```

与非虚继承相比，虚继承会带来哪些额外开销？

A. 无额外开销，虚继承只是编译器标记
B. 每个虚继承子类对象含一个指向虚基类的指针（vbptr），`sizeof` 通常增大
C. 函数调用速度加倍变慢
D. 编译时间变长，运行时无任何开销
