---
qid: cpp-iv-move-004
type: short
kp: [cpp-interview]
difficulty: medium
tags: [Google, Meta]
rubric:
  - 转发引用（forwarding reference）= 函数模板中 T&& 且 T 是被推导的类型参数
  - 普通右值引用 T&&：T 是具体类型（非推导），只绑定右值
  - 关键区别：auto&& 也是转发引用；成员函数模板中 T&& 通常也是转发引用
  - 转发引用可绑定左值也可绑定右值（通过引用折叠）
  - 加分：列举非转发引用的典型陷阱（std::vector<T>::push_back(T&&) 不是转发引用）
---

# 什么是转发引用（forwarding reference）？和右值引用 `T&&` 如何区分？

## 参考答案

### 右值引用（rvalue reference）

当 `T` 是**已知的具体类型**（不通过模板参数推导）时，`T&&` 是普通右值引用：

```cpp
void f(std::string&& s);  // 普通右值引用：只接受右值

std::string s = "hi";
f(s);            // 错误：s 是左值
f(std::move(s)); // OK
f("hello");      // OK：字面量是右值
```

### 转发引用（forwarding reference）

当满足以下两个条件时，`T&&` 是**转发引用**：

1. `T` 是通过**模板参数推导**得到的类型
2. 形式严格为 `T&&`（不能是 `const T&&`、`std::vector<T>&&` 等）

```cpp
template<typename T>
void g(T&& x);   // 转发引用：可绑定左值或右值

int a = 1;
g(a);            // T 推导为 int&，x 类型为 int& &&  → int&（折叠）
g(1);            // T 推导为 int，  x 类型为 int&&
g(std::move(a)); // T 推导为 int，  x 类型为 int&&
```

`auto&&` 也是转发引用（auto 相当于模板参数推导）：

```cpp
auto&& r1 = a;   // r1 是 int&（绑定左值）
auto&& r2 = 42;  // r2 是 int&&（绑定右值）
```

### 区分口诀

| 形式 | 是否转发引用？ | 说明 |
|------|--------------|------|
| `template<T> void f(T&&)` | 是 | T 被推导 |
| `auto&&` | 是 | auto 推导 |
| `void f(int&&)` | 否 | T 是具体类型 |
| `template<T> void f(const T&&)` | 否 | 有 const 修饰 |
| `template<T> void f(std::vector<T>&&)` | 否 | T 在内层，不是外层 T&& |

### 经典陷阱：`push_back` vs `emplace_back`

```cpp
template<class T>
class vector {
public:
    void push_back(T&& x);       // 不是转发引用！T 是类模板参数，非函数模板参数
                                  // T 已在类实例化时确定，这里只绑定右值

    template<class... Args>
    void emplace_back(Args&&... args); // 是转发引用！Args 在此函数调用时推导
};
```

这是高频考点：`push_back(T&&)` 只接受右值（因为 `T` 是类级别的模板参数），而 `emplace_back(Args&&...)` 是真正的转发引用。

### 本质原因

转发引用能绑定左值的原因是**引用折叠**（详见引用折叠规则题）：当 `T` 被推导为 `int&` 时，`T&&` 变成 `int& &&`，折叠为 `int&`，从而绑定左值。
