---
qid: cpp-x-tmpl-move-002
type: single
kp: [cpp-templates, cpp-move-semantics]
primary_kp: cpp-templates
difficulty: medium
answer_key: B
---

下列两个函数模板的参数类型 `T&&` 含义是否相同？

```cpp
#include <utility>

template <class T>
void f(T&& x);              // (1) 模板函数参数

template <class T>
struct S {
    void g(T&& x);          // (2) 类模板的成员函数参数
};
```

A. 两者都是转发引用，可绑定左值或右值
B. (1) 是转发引用；(2) 是右值引用，只能绑定右值
C. (1) 是右值引用；(2) 是转发引用
D. 两者都是右值引用

---

## Explanation

转发引用（universal reference / forwarding reference）成立的 **充要条件** 是：参数类型形如 `T&&`，且 `T` 是 **该函数自己的模板参数**，从而需要类型推导。

- **(1)**：`f` 是函数模板，调用 `f(x)` 时 `T` 需要从实参推导，于是 `T&&` 是转发引用。传 `int` 左值时 `T = int&`，参数折叠为 `int&`；传 `int{}` 右值时 `T = int`，参数为 `int&&`。
- **(2)**：`g` 是 **类模板** `S<T>` 的成员函数，`T` 在 `S<T>` 实例化时（如 `S<int>`）就已经被确定，调用 `g(x)` 时并不会重新推导 `T`。因此 `T&&` 就是普通的右值引用，绑定到 `S<int>::g` 时即 `int&&`，传左值会编译失败。

如果想在类模板成员里实现转发引用，必须让成员函数自身带一个新的模板参数：

```cpp
template <class T>
struct S {
    template <class U>
    void g(U&& x);          // U 是 g 自己的模板参数，这才是转发引用
};
```
