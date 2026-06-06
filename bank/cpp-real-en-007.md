---
qid: cpp-real-en-007
type: short
kp: [cpp-polymorphism, cpp-special-members]
primary_kp: cpp-polymorphism
difficulty: hard
tags: [interview-real, interviewbit]
rubric:
  - （2分）解释 vtable 是什么：每个含有虚函数的类有一个 vtable，其中存储虚函数指针
  - （2分）解释 vptr（虚表指针）：每个对象在内存开头有一个隐藏的 vptr 指向其类的 vtable
  - （2分）解释动态派发流程：调用虚函数时通过 vptr 找到 vtable，再通过函数地址跳转
  - （1分）说明运行时类型信息（RTTI）的作用
  - （1分）说明虚函数调用的运行时开销（一次间接寻址，无法内联）
  - --
---
请简述虚函数表（vtable）的机制和动态派发（dynamic dispatch）的执行流程。

**评分标准（rubric）：**
- （2分）解释 vtable 是什么：每个含有虚函数的类有一个 vtable，其中存储虚函数指针
- （2分）解释 vptr（虚表指针）：每个对象在内存开头有一个隐藏的 vptr 指向其类的 vtable
- （2分）解释动态派发流程：调用虚函数时通过 vptr 找到 vtable，再通过函数地址跳转
- （1分）说明运行时类型信息（RTTI）的作用
- （1分）说明虚函数调用的运行时开销（一次间接寻址，无法内联）

---

**解析：**

**vtable 机制：**
每个包含虚函数（或其继承链中有虚函数）的类，在编译期生成一个虚函数表（vtable），表中按声明顺序存储虚函数指针。每个对象在内存起始位置有一个隐藏的 `vptr` 指针，指向所属类的 vtable。

**动态派发流程：**
```
obj.virtual_func(args)
  → obj.vptr  → 类的 vtable
  → 从 vtable 中取出对应槽位的函数地址
  → 跳转执行
```

这个过程在运行时决定调用哪个函数版本（而非编译期），因此称为动态绑定（dynamic binding）或后期绑定（late binding）。代价是一次额外的指针间接寻址，且虚函数无法内联（inline）。

**来源：** InterviewBit "C++ Interview Questions" — Virtual Table / vtable

## Explanation

本题评分重点是说明 vtable 是类级别的虚函数入口表，vptr 是对象里的隐藏指针，虚调用通过 vptr 找到 vtable 槽位再跳转。这个过程使 Base* 或 Base& 能在运行期调用派生类覆盖版本，也解释了动态绑定的来源。还应提到 RTTI 通常与虚表相关，虚调用有一次间接寻址并可能阻碍内联。常见误区是把普通非虚函数也放进虚表，或认为虚函数表每个对象各有一份。
