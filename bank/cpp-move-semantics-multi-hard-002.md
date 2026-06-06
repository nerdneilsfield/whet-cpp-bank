---
qid: cpp-move-semantics-multi-hard-002
type: multi
kp: [cpp-move-semantics]
difficulty: hard
answer_key: [A, B, D]
---
下面两段代码中的 `T&&`，哪些说法正确？

```cpp
template<typename T>
void f(T&& x);                  // (1)

void g(int&& x);                // (2)

template<typename T>
class C {
public:
    void h(T&& x);              // (3)
};
```

A. (1) 的 `T&&` 是"转发引用/universal reference"（Scott Meyers 命名），可绑定左值或右值，因为 `T` 处于类型推导上下文。
B. (2) 的 `int&&` 是普通右值引用，只能绑定 `int` 右值，传入左值会编译失败。
C. (3) 的 `T&&` 也是转发引用，因为成员函数有 `T` 在其中。
D. 区分关键在于"`T` 是否在该函数调用处发生类型推导"。(3) 的 `T` 在类实例化时已经确定，调用 `h` 时不再推导 `T`，所以 (3) 是普通右值引用。

---

**解析：**

A 正确：转发引用必须满足两个条件：(a) 形式精确为 `T&&`（不能是 `const T&&` 或 `std::vector<T>&&`），(b) `T` 在该调用处发生模板类型推导。(1) 完全符合，是 Scott Meyers 提出的 universal/forwarding reference。
B 正确：`int&&` 写明具体类型，没有类型推导，是普通右值引用；传左值 `int i; g(i);` 不能绑定，编译失败。
C 错误：成员函数 `h(T&& x)` 中，`T` 是类模板参数，类实例化时已经确定（如 `C<int>`），调用 `h` 时不再推导 `T`，因此 `T&&` 是普通右值引用而非转发引用。这是 Effective Modern C++ Item 24 的经典陷阱。
D 正确：正是 C 错误的解释——是否构成转发引用的判据是"该调用处是否发生 `T` 的推导"。

## Explanation

A、B、D 正确：只有在函数模板调用处发生类型推导的精确 `T&&` 才是转发引用。普通 `int&&` 只能绑定右值，而类模板成员里的 `T` 已在类实例化时确定，`T&&` 不再是转发引用。常见误区是看到 `T&&` 就一律称为 universal reference，忽略了“是否正在推导”的前提。
