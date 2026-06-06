---
qid: cpp-real-nk-027
type: single
kp: [cpp-lambdas]
primary_kp: cpp-lambdas
difficulty: medium
answer_key: C
tags: [interview-real, bytedance]
---

```cpp
int x = 10;
auto f = [x](int y) { return x + y; };
std::cout << f(5);
```

lambda 表达式在 C++ 中本质上等价于：

A. 一个普通的函数指针
B. 一个 std::function 对象
C. 一个**编译器生成的匿名类**的实例，重载了 `operator()`
D. 一个宏展开

---

**解析：**

C++ lambda 是**匿名 functor 的语法糖**。编译器为上述代码生成等价的：

```cpp
struct __lambda_1 {
    int x;  // 按值捕获
    __lambda_1(int x_) : x(x_) {}
    int operator()(int y) const { return x + y; }
};

__lambda_1 f(10);
f(5);
```

特点：
- **按值捕获 `[x]`** → 作为成员变量
- **按引用捕获 `[&x]`** → 作为引用成员
- **不捕获 `[]`** → 可以隐式转换为函数指针
- `operator()` 默认是 `const`（因此不能修改按值捕获的变量，除非加 `mutable`）

性能上比 `std::function` 快（无虚函数调用、可内联），但每个 lambda 都是独立类型，因此 `decltype(f1) != decltype(f2)`。

**来源：** 字节 C++11 面试题 / cppreference

## Explanation

正确答案是 C。
C++ lambda 是匿名 functor 的语法糖。编译器为上述代码生成等价的： 特点： 按值捕获 [x] → 作为成员变量 按引用捕获 [&x] → 作为引用成员 不捕获 [] → 可以隐式转换为函数指针 operator() 默认是 const（因此不能修改按值捕获的变量，除非加 mutable） 性能上比 std::function 快（无虚函数调用、可内联），但每个 lambda 都是独立类型，因此 decltype(f1) != decltype(f2)。
