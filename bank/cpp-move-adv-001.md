---
qid: cpp-move-adv-001
type: single
kp: [cpp-move-semantics]
difficulty: medium
answer_key: B
---

下列函数模板中，`T&&` 是**转发引用**（forwarding reference）的是哪一个？

```cpp
// A
template<typename T>
void f(const T&& x);

// B
template<typename T>
void g(T&& x);

// C
void h(int&& x);

// D
template<typename T>
struct Foo {
    void bar(T&& x);
};
```

A. A，因为有 `&&`
B. B，`T&&` 且 T 是无 cv 限定的推导模板参数
C. C，`int&&` 是右值引用
D. D，成员函数里的 `T&&` 也是转发引用

---

**解析：**

转发引用（forwarding reference，又称 universal reference）的条件：
1. 形如 `T&&`，其中 T 是**当前函数模板**直接推导的模板参数；
2. T **不带任何 cv 限定**（`const T&&` 不是转发引用）。

- A：`const T&&` 有 cv 限定，是普通右值引用。
- B：满足两个条件，是转发引用，可绑定左值和右值。
- C：`int&&` 是具体类型的右值引用，不涉及模板推导。
- D：`Foo<T>` 的 T 在实例化时已经确定，`bar(T&& x)` 里 T 不再被推导，因此是普通右值引用。

## Explanation

正确答案是 B，转发引用必须精确形如 `T&&`，且 `T` 是当前函数模板直接推导出的无 cv 限定模板参数。A 的 `const T&&` 是普通右值引用，C 的 `int&&` 不是模板推导，D 中类模板参数 `T` 已在类实例化时确定，成员函数调用时不再推导。常见误区是只要看到 `&&` 就认为是转发引用。
