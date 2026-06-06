---
qid: cpp-x-inh-smf-002
type: single
kp: [cpp-inheritance, cpp-special-members]
primary_kp: cpp-special-members
difficulty: medium
answer_key: C
---

下列代码中，`delete p` 的行为是？

```cpp
#include <iostream>

struct Base {
    ~Base() { std::cout << "~Base "; }   // 非 virtual
};

struct Derived : Base {
    int* data;
    Derived() : data(new int[1024]) {}
    ~Derived() { delete[] data; std::cout << "~Derived "; }
};

int main() {
    Base* p = new Derived;
    delete p;       // ← 这里
}
```

A. 合法，输出 `~Derived ~Base`
B. 合法，输出 `~Base` 后调用 Derived 析构清理资源
C. 未定义行为，且即便侥幸只输出 `~Base`，`data` 也会泄漏
D. 编译错误，因为基类析构非 virtual

---

**解析：**

[expr.delete]/3：通过指向基类的指针 `delete` 一个派生类对象时，如果基类的析构函数 **不是 virtual**，行为是 **未定义行为（UB）**。

实际表现通常如下：
1. 只调用 `~Base()`，`~Derived()` 不被执行，导致 `data` 数组泄漏。
2. 如果 `Derived` 与 `Base` 的内存布局不同（例如多重继承场景下基类子对象偏移非 0），`delete` 收到的指针可能不是 `operator new` 返回的原始地址，进一步引发堆破坏。

正确做法是 **将多态基类的析构函数声明为 `virtual`**：

```cpp
struct Base {
    virtual ~Base() = default;   // 关键
};
```

这是 Scott Meyers《Effective C++》Item 7 的核心戒律：「Declare destructors virtual in polymorphic base classes.」

如果某个类 **永远不会被作为基类使用**，则不需要付出 virtual 的代价（vtable 指针、间接调用）；可以用 `final` 关键字阻止继承：

```cpp
struct NonBase final { ~NonBase() = default; };
```

选项 A/B 假设了正确多态析构，与本题前提矛盾。D 错：编译器不会报错，UB 通常静默通过。