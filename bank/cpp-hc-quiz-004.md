---
qid: cpp-hc-quiz-004
type: single
kp: [cpp-classes, cpp-undefined-behavior]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [interview-real, handcrafted, language-lawyer]
---
根据 C++17 标准，以下程序的输出是？

```cpp
#include <iostream>

struct Base {
    Base()  { init(); }
    virtual ~Base() = default;
    virtual void init() { std::cout << "Base::init "; }
    void run() { init(); }
};

struct Derived : Base {
    Derived() : Base() {}
    void init() override { std::cout << "Derived::init "; }
};

int main() {
    Derived d;
    d.run();
}
```

A. `Base::init Derived::init`
B. `Base::init Derived::init`，但注意构造时调的是 `Base::init`
C. `Derived::init Derived::init`
D. 行为未定义——构造函数中调用虚函数是 UB

---

**解析：**

选 B（A、B 文字相同但 B 解释更明确）。这道题考察"**构造/析构函数中的虚函数调用**"这条 C++ 经典规则。

**规则**（[class.cdtor]/4）：
> Member functions, including virtual functions, can be called during construction or destruction. **When a virtual function is called directly or indirectly from a constructor or from a destructor, the function called is the final overrider in the constructor's or destructor's class** and not one overriding it in a more-derived class.

翻译：构造/析构函数中调用虚函数，**不进行动态派发**——调到的是**当前类**的版本，而不是派生类的覆盖。

**执行流程**：

1. `Derived d;` 触发构造
2. 进入 `Base` 子对象的构造：
   - 此时 vptr 指向 `Base` 的 vtable
   - `init()` 调用解析为 `Base::init` → 输出 `Base::init `
3. 进入 `Derived` 子对象构造（这里什么也不做）
   - vptr 切到 `Derived` 的 vtable
4. `d.run()` 调用：
   - `run` 是 `Base` 的普通成员函数
   - 在 `run` 内部调用 `init()`——**但此时 d 已构造完成**，vptr 是 `Derived` 的
   - 动态派发到 `Derived::init` → 输出 `Derived::init `

输出：`Base::init Derived::init`。

**为什么标准这样设计**？

构造时基类先构造，派生类尚未初始化。如果允许动态派发到派生类的 `init`，派生类的成员还是垃圾值——这会让对象在构造中期处于半成品状态被使用。标准选择**静态绑定到当前类的版本**作为安全默认。

**C 错**的原因：以为构造时也走动态派发——这是新人最大的误解。

**D 错**——构造/析构函数中调用虚函数**不是 UB**，是有明确定义的行为，只是不做动态派发。

**实践建议**：永远不要在构造/析构函数中调用虚函数。即使你"知道规则"，下一个读代码的人会迷惑。如果必须做"构造后初始化"，提供一个独立的 `init()` 工厂函数，构造完再显式调用。

**陷阱变种**：纯虚函数在构造/析构中被调用 → **运行时调 `std::terminate`**（因为 `Base::init = 0` 没定义，跳过去执行就崩）。这才是 UB 边界的东西，是真正的"灾难性陷阱"。

**来源：** 手写题。规则见 ISO/IEC 14882:2017 §15.7.4 [class.cdtor]；Scott Meyers, *Effective C++* Item 9: "Never call virtual functions during construction or destruction"。
