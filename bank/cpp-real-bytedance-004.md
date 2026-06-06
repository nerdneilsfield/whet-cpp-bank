---
qid: cpp-real-bytedance-004
type: single
kp: [cpp-move-semantics, cpp-templates]
primary_kp: cpp-move-semantics
difficulty: hard
answer_key: B
tags: [interview-real, bytedance]
---
```cpp
template<typename T>
void f(T&& arg) {       // T&& 在这里不是右值引用，是"通用引用"
    // ...
}

void g(int&& arg) {     // int&& 是右值引用
    // ...
}

int x = 42;
f(x);          // T 推导为 int&，arg 类型是 int&（reference collapsing）
f(42);         // T 推导为 int，arg 类型是 int&&
g(x);          // 编译错误：不能从 lvalue 绑定到右值引用
g(42);         // OK
```
关于"通用引用"（universal reference / forwarding reference）的判断，以下说法**正确**的是：

A. 所有带 `&&` 的参数都是右值引用
B. 只有在**类型推导**的上下文中（如模板参数 T、auto），`T&&` 才是通用引用；具体类型的 `int&&` 始终是右值引用
C. 通用引用就是右值引用的别名，没区别
D. `const T&&` 也是通用引用

---

**解析：**

选 B。这是 Scott Meyers 总结的关键规则。

**通用引用（universal reference）的精确条件：**
1. 必须是 `T&&` 的形式
2. T 必须是**通过类型推导**得出的（模板参数或 auto）

**reference collapsing 规则：**
- `T& &` → `T&`
- `T& &&` → `T&`
- `T&& &` → `T&`
- `T&& &&` → `T&&`

**应用：**
```cpp
template<typename T> void f(T&& arg);

f(x);   // x 是 int lvalue → T 推导为 int& → arg 类型 int& && → int&
f(42);  // 42 是 int rvalue → T 推导为 int → arg 类型 int&&
```

**反例（不是通用引用）：**
```cpp
template<typename T>
void g(std::vector<T>&& v);  // vector<T>&& 不是通用引用（vector<T> 不是 T 本身）

void h(int&& x);             // int&& 是右值引用，没有类型推导

template<typename T>
void k(const T&& x);         // const T&& 不是通用引用（带 const 修饰）
```

**配套：** 通用引用要用 `std::forward<T>(arg)` 实现完美转发（perfect forwarding），而右值引用用 `std::move`：
```cpp
template<typename T>
void wrapper(T&& arg) {
    real_func(std::forward<T>(arg));  // 保持值类别
}
```

**来源：** 字节 C++11 高级面试（参考：Effective Modern C++ Item 24-26）

## Explanation

正确答案是 B。
选 B。这是 Scott Meyers 总结的关键规则。
*通用引用（universal reference）的精确条件： 必须是 T&& 的形式 T 必须是通过类型推导得出的（模板参数或 auto） *reference collapsing 规则： T& & → T& T& && → T& T&& & → T& T&& && → T&& *应用： *反例（不是通用引用）： *配套： 通用引用要用 std::forward<T>(arg) 实现完美转发（perfect forwarding），而右值引用用 std::move。
