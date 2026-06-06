---
qid: cpp-inh-hard-001
type: single
kp: [cpp-inheritance]
difficulty: hard
answer_key: C
---

关于虚继承引入的额外开销，以下说法最准确的是？

```cpp
struct Base { int b; };
struct M1 : virtual Base { int m1; };
struct M2 : virtual Base { int m2; };
struct D  : M1, M2 { int d; };
```

A. 虚继承没有任何运行期开销，仅在编译期合并基类
B. 虚继承使每个虚基类必须新增一个 `vptr`，因此对象增加 `sizeof(void*) * 虚基类数量`
C. 典型实现下，每个含虚基类的最派生对象会通过额外的"虚基偏移表"（vbase offset，通常存于 vptr 关联的虚表中）定位虚基类，访问 `b` 需要一次间接寻址
D. 虚继承使所有成员访问都变为动态分发，性能明显下降

## 解析

虚继承解决菱形继承下共享基类的"唯一性"问题。典型实现（Itanium ABI）中，编译器在派生对象布局里为每个含虚基的子对象插入一个偏移指针（或合并到 vptr 指向的虚表段中），运行期通过该偏移定位**共享的虚基子对象**。访问虚基成员（如 `d.b`）需经一次额外的间接寻址（先读 vptr / vbase offset，再加偏移），这是主要运行期成本。虚继承既不会让每个虚基都"新增一个完整 vptr"（B 不准），也不会让普通成员访问变为动态分发（D 不准）。A 错：实测有可观开销。