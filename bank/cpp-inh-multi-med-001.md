---
qid: cpp-inh-multi-med-001
type: multi
kp: [cpp-inheritance]
difficulty: medium
answer_key: [A, B, D]
---
关于虚函数的特征，**哪些说法是正确的**？（多选）

A. 虚函数通过 vtable / 虚指针在运行期分派。
B. 构造函数不能是虚函数。
C. 静态成员函数可以声明为 virtual。
D. 析构函数可以并且通常应该声明为 virtual（在多态基类中）。

---

**解析：**

A 正确：典型实现使用 vptr+vtable 实现动态分派。
B 正确：构造对象时尚未有虚表机制，构造函数不能是虚函数。
C 错误：静态成员函数与对象实例无关，不能声明为 virtual。
D 正确：多态基类应使用虚析构以保证 `delete base_ptr;` 正确析构派生对象。