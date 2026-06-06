---
qid: cpp-real-nk-multi-010
type: multi
kp: [cpp-templates, cpp-classes]
primary_kp: cpp-templates
difficulty: hard
answer_key: [A, B, D]
tags: [interview-real, alibaba]
---

```cpp
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class Concrete : public Base<Concrete> {
public:
    void implementation() { std::cout << "Concrete"; }
};
```

CRTP（Curiously Recurring Template Pattern）的特点包括：

A. **实现"静态多态"**，无虚函数开销（无 vtable / vptr / 动态查找）
B. **常用于实现 mixin、`enable_shared_from_this`、表达式模板**
C. CRTP 类的指针可以通过基类指针进行动态绑定
D. **缺点是不同的派生类生成不同的基类实例化，代码膨胀；且基类无法做异构容器（不能存 `vector<Base*>`）**

---

**解析：**

CRTP 关键：派生类把自己作为基类的模板参数。

A 对：编译期 `static_cast<Derived*>(this)` 把基类指针转回派生类，调用 `implementation()` 是静态绑定（编译期解析），无虚函数开销，可被内联。

B 对：CRTP 的典型应用：
- `std::enable_shared_from_this<T>`：经典 CRTP
- 表达式模板（Eigen 库）：消除临时对象
- mixin（混入）：复用代码无需虚函数

C **错**：CRTP **没有动态多态**。`Base<A>` 和 `Base<B>` 是两个**不同的类型**，无法用同一个基类指针处理。

D 对：每个派生类实例化一次基类（代码膨胀）；无法异构容器（这点与 D 一致是 CRTP 的根本限制）。需要异构时仍需要虚函数。

设计上：CRTP 优势在性能（无 vtable）和编译期检查；劣势是不能放进 `vector<Base*>`。

**来源：** 阿里秋招 C++ 设计模式面试题 / Modern C++ Design