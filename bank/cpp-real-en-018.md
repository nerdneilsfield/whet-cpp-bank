---
qid: cpp-real-en-018
type: short
kp: [cpp-inheritance]
primary_kp: cpp-inheritance
difficulty: hard
tags: [interview-real, interviewbit]
rubric:
  - （2分）描述菱形继承场景：D 继承自 B 和 C，B 和 C 都继承自 A
  - （2分）指出问题：D 中包含两份 A 的子对象，导致二义性
  - （2分）说明虚继承语法：`class B : virtual public A`
  - （1分）说明解决方法：虚继承让 D 中只有一份 A 子对象，由最派生类（D）负责构造 A
  - （1分）说明代价：vtable 开销，间接访问，构造顺序变化
  - --
---
简述菱形继承（Diamond Inheritance）问题及虚继承（virtual inheritance）如何解决。

**评分标准（rubric）：**
- （2分）描述菱形继承场景：D 继承自 B 和 C，B 和 C 都继承自 A
- （2分）指出问题：D 中包含两份 A 的子对象，导致二义性
- （2分）说明虚继承语法：`class B : virtual public A`
- （1分）说明解决方法：虚继承让 D 中只有一份 A 子对象，由最派生类（D）负责构造 A
- （1分）说明代价：vtable 开销，间接访问，构造顺序变化

---

**解析：**

**菱形继承问题：**
```
    A
   / \
  B   C
   \ /
    D
```
D 继承自 B 和 C，B 和 C 都继承自 A。如果不加特殊处理，D 中会包含两份 A 的子对象（一份来自 B，一份来自 C），导致：
1. 通过 D 访问 A 的成员时出现二义性（编译器不知道走哪条路径）
2. A 的构造函数被调用两次

**虚继承解决：**
```cpp
class A { public: int x; };
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};
```
使用 `virtual` 继承后，D 中只有**一份**共享的 A 子对象。由最派生类（D）直接负责构造该共享子对象。代价是额外 vtable 开销和访问 A 成员时多一次间接寻址。

**来源：** InterviewBit "C++ Interview Questions" — Diamond Problem / Virtual Inheritance

## Explanation

本题评分重点是描述菱形继承：D 同时经 B 和 C 继承 A，普通继承会让 D 中出现两份 A 子对象，访问 A 成员时产生二义性。虚继承通过 class B : virtual public A 让最终派生类共享一份 A 子对象，并由最派生类负责构造它。代价是对象布局更复杂，访问虚基类通常需要额外间接寻址。常见误区是以为 virtual 写在函数上能解决菱形继承；这里需要的是虚继承。
