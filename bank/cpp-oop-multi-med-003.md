---
qid: cpp-oop-multi-med-003
type: multi
kp: [cpp-special-members]
difficulty: medium
answer_key: [A, B, D]
---
关于 C++ "五法则"（Rule of Five）以及编译器自动生成的特殊成员函数，**哪些说法是正确的**？（多选）

```cpp
class A {
    int* p;
public:
    A() : p(new int(0)) {}
    ~A() { delete p; }
};
```

A. 类 `A` 自定义了析构函数但未定义拷贝构造/拷贝赋值，编译器仍生成默认的浅拷贝版本，这通常导致 double free
B. 用户声明了任意一个拷贝/移动操作或析构函数，编译器**不再自动生成**移动构造/移动赋值（仅可能生成已弃用的拷贝版本）
C. `= default` 显式让编译器生成默认实现，与"完全不写"完全等价，没有任何差异
D. 当类持有不可拷贝的资源（如 `unique_ptr`），应将类显式声明为只移类型（删除拷贝、提供移动）

---

**解析：**

A 正确：定义析构却未管理拷贝即"半 RAII"，浅拷贝两个对象指向同一内存，析构两次造成 double free。
B 正确：用户提供任意一个特殊成员函数会抑制移动函数的自动生成；拷贝函数虽仍可能生成但已被标准弃用（deprecated since C++11 if dtor/copy-ctor user-declared）。
C 错误：`= default` 与"不写"**有差异**：① `=default` 允许在类外延后定义；② 影响 trivially copyable/standard-layout 等性质；③ 与访问控制结合（如 `public: A() = default;` 与 `private: A();` 行为不同）；④ 显式默认会"算作用户声明"，影响隐式移动生成。
D 正确：标准做法——`class X { X(const X&) = delete; X& operator=(const X&) = delete; X(X&&) = default; X& operator=(X&&) = default; };`

## Explanation

A、B、D 正确：自定义析构函数但不定义拷贝控制会留下默认浅拷贝，资源类很容易 double free。用户声明特殊成员会影响隐式移动生成，`= default` 也会改变“是否用户声明”的语义。常见误区是只写析构就完成了资源管理；持有资源的类型应遵循五法则或尽量用零法则。
