---
qid: cpp-real-short-004
type: short
kp: [cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: hard
tags: [interview-real, alibaba]
rubric:
  - 解释 vptr 的位置（每个多态对象开头 8 字节，指向 vtable）（1 分）
  - 单继承 vtable 布局：基类虚函数在前，派生类覆盖后替换为派生版本，新虚函数追加在末（1 分）
  - 多继承 vtable 布局（thunk/adjustor 修正 this 指针）（1 分）
  - 画出示意图（合理结构即可）（1 分）
  - 清楚说明动态分发的完整路径：obj.vptr → vtable → function entry（1 分）
---
解释 C++ 虚函数表（vtable）的内存布局，画出示意图，说明单继承和多继承的区别，并指出对象在内存中的虚表指针（vptr）位置。

**rubric (5 分)：**
- [  ] 解释 vptr 的位置（每个多态对象开头 8 字节，指向 vtable）（1 分）
- [  ] 单继承 vtable 布局：基类虚函数在前，派生类覆盖后替换为派生版本，新虚函数追加在末（1 分）
- [  ] 多继承 vtable 布局（thunk/adjustor 修正 this 指针）（1 分）
- [  ] 画出示意图（合理结构即可）（1 分）
- [  ] 清楚说明动态分发的完整路径：obj.vptr → vtable → function entry（1 分）

**期望答案：**

**虚函数表（vtable）是编译器为每个多态类生成的函数指针数组。**

**单继承布局：**
```cpp
class Base {
public:
    virtual void f1();  // vtable[0]
    virtual void f2();  // vtable[1]
    virtual void f3();  // vtable[2]
};

class Derived : public Base {
public:
    void f1() override;  // 覆盖后：vtable[0] = &Derived::f1
    virtual void f4();   // 新增：vtable[3] = &Derived::f4
};
```

**单继承 vtable 示意图：**
```
对象 Derived d:
[ vptr ] → [ vtable of Derived ]
            ┌───────────────────┐
            │ typeinfo (RTTI)   │
            │ Derived::f1       │  ← 覆盖 Base::f1
            │ Base::f2          │  ← 未覆盖
            │ Base::f3          │  ← 未覆盖
            │ Derived::f4       │  ← 新增
            └───────────────────┘
```

**多继承布局（多个 vptr）：**
```cpp
class A { virtual void fa(); };
class B { virtual void fb(); };
class C : public A, public B {
    void fa() override;
    void fb() override;
    virtual void fc();
};
```
```
对象 C:
[ vptr_A ] → [ vtable for A part ]
              ┌────────────────────┐
              │ top_offset = 0     │
              │ C::fa              │
              │ C::fc              │  ← 新虚函数放在第一个基类
              └────────────────────┘
[ vptr_B ] → [ vtable for B part ]
              ┌────────────────────┐
              │ top_offset = -X    │  ← adjustor: this -= X → C*
              │ thunk: C::fb       │  ← thunk 调整 this 后跳转到 C::fb
              └────────────────────┘
```

**动态分发流程：**
1. `obj->f1()` → 取 obj 的 vptr → vtable
2. `vtable[0]` 是函数地址 → call 该地址
3. 对有 thunk 的场景：先执行 thunk 调整 this → 再跳转真正的函数

**来源：** 阿里/腾讯虚函数经典题（参考：《Inside the C++ Object Model》