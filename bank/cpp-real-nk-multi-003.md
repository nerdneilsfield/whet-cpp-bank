---
qid: cpp-real-nk-multi-003
type: multi
kp: [cpp-classes, cpp-functions]
primary_kp: cpp-classes
difficulty: medium
answer_key: [A, B, C, D]
tags: [interview-real, nowcoder]
---

```cpp
class Foo {
    int x;
public:
    const int* getPtr() const;
    int* const getConstPtr();
    void setX(int v);
};
```

下列关于 `const` 修饰位置的描述，正确的有：

A. **`int const* p` 与 `const int* p` 等价**，都是指向 const int 的指针（可改指针，不可改对象）
B. **`int* const p`** 是 const 指针，指针不能改变指向，但可以通过它修改对象
C. **类的成员函数末尾的 const**（如 `int getX() const`）表示该函数不会修改对象，可被 const 对象调用
D. **返回值类型 const（如 `const int foo()`）** 对内置类型返回意义不大，但对返回引用/指针（如 `const T& at()`）能防止调用方修改

---

**解析：**

记忆法："**const 在 * 左边修饰类型，在 * 右边修饰指针**"

```cpp
const int* p;  // 修饰 int，p 指向常量
int const* p;  // 同上，等价
int* const p;  // 修饰 p，p 是常量指针
const int* const p;  // 双 const，指针和指向都不可变
```

**const 成员函数**：
- 函数末尾的 const 修饰 `*this`（即 `this` 指向 const Foo）
- const 函数内不能修改成员（除非成员是 `mutable`）
- 非 const 对象既可以调用 const 函数，也可以调用非 const 函数
- const 对象只能调用 const 函数

**const 返回值**：
- 返回内置类型（值类型）加 const 几乎没意义：`const int foo()` 调用方 `int x = foo()` 仍可拷贝
- 但返回引用/指针：`const string& at(size_t i)` 防止 `s.at(0) = 'X'`

D 是设计 const-correctness 的核心实践。

**来源：** 虎牙 C++ 面试题 / Effective C++ Item 3