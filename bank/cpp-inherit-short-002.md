---
qid: cpp-inherit-short-002
type: short
kp: [cpp-inheritance]
difficulty: medium
rubric:
  - 解释 object slicing：将派生类对象按值赋给/传给基类时，派生部分被切掉
  - 指出动态类型变为基类，虚函数不会再分派到派生
  - 给出避免方式（通过基类指针或引用传递）
  - 可指出使用智能指针管理多态对象
---
请解释 C++ 中的对象切片（object slicing）现象及其避免方式。

---

**参考答案：**

当一个派生类对象按值赋给基类对象、或按值传给基类形参时，只有基类那部分子对象被拷贝/移动，派生类中新增的成员被"切掉"，得到的是一个纯基类对象，且其动态类型也是基类，调用虚函数不再分派到派生实现。要避免切片，应通过基类指针或引用传递多态对象（`void f(Base&)` 或 `void f(Base*)`），或使用 `std::unique_ptr<Base>` / `std::shared_ptr<Base>` 管理动态对象，从而保留派生类型信息。