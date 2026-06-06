---
qid: cpp-smf-med-005
type: single
kp: [cpp-special-members]
difficulty: medium
answer_key: C
---

打算把 `Base` 用作多态基类（会有 `Base* p = new Derived;` 然后 `delete p;`）。如果只把析构函数声明为 `virtual` 而不写其他特殊成员，最容易触发的后果是？

```cpp
struct Base {
    virtual ~Base() = default;     // 仅声明虚析构
    // 其他特殊成员一律未声明
};
```

A. 拷贝构造和拷贝赋值会被隐式删除，无法拷贝
B. 移动构造和移动赋值依然会被隐式生成，行为完全正常
C. 移动构造和移动赋值被**抑制**（不生成），所有“移动”都退化为拷贝
D. 类不能被继承，因为没有显式声明拷贝构造

---

**解析：**

Rule of Five 在此处的副作用常被忽略：用户**显式声明**了析构函数（即使是 `= default`），编译器就**不再隐式生成**移动构造与移动赋值，但仍会隐式生成拷贝构造与拷贝赋值（除非也被声明）。这是为了向后兼容 C++03 代码。

结果是 `Derived d2 = std::move(d1);` 形式的“移动”仍能编译，但走的是拷贝路径——对持有大资源的派生类性能损失明显，对持有 unique 资源的派生类则可能编译错。

修复方法：把五个特殊成员全部明确列出。多态基类的标准模板是

```cpp
struct Base {
    Base()                                = default;
    virtual ~Base()                       = default;
    Base(const Base&)                     = default;
    Base& operator=(const Base&)          = default;
    Base(Base&&) noexcept                 = default;
    Base& operator=(Base&&) noexcept      = default;
};
```

更激进的方案：把拷贝/移动都 `= delete`，强制派生类自己处理切片问题（Scott Meyers, *Effective Modern C++* item 17）。

## 解析

正确答案是 C，即使析构函数写成 `virtual ~Base() = default`，它仍是用户声明的析构函数，会抑制隐式移动构造和移动赋值。结果是看似移动的操作可能退化为拷贝，或在派生类含不可拷贝资源时失败。多态基类常需要显式默认或删除五个特殊成员，避免隐式规则带来的意外。
