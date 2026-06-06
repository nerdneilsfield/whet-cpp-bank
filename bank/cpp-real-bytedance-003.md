---
qid: cpp-real-bytedance-003
type: single
kp: [cpp-lambdas, cpp-classes]
primary_kp: cpp-lambdas
difficulty: hard
answer_key: D
tags: [interview-real, bytedance]
---
```cpp
int x = 10;
auto lam = [x](int y) mutable { x += y; return x; };

// lambda 等价于以下匿名结构体（简化）:
// struct __Lam {
//     int x;
//     __Lam(int x_) : x(x_) {}
//     int operator()(int y) { x += y; return x; }
// };
```
关于 lambda 表达式的本质，以下说法**不正确**的是：

A. lambda 的捕获列表本质是匿名类的成员变量，按值捕获即拷贝，按引用捕获即引用成员
B. 不带 `mutable` 的 lambda，其 `operator()` 是 const 成员函数，因此不能修改按值捕获的变量
C. 不捕获任何变量的 lambda 可以隐式转换为对应的函数指针
D. lambda 的类型在不同翻译单元中是相同的，因此可以通过函数声明传递

---

**解析：**

选 D（说法错误）。

**lambda 本质：编译器生成的匿名 closure 类型。** 

每个 lambda 表达式生成一个**唯一的**匿名类（class），同源代码、同捕获列表、同函数体也是不同类型。这就是为什么：
- `auto` 是写 lambda 的唯一方式（你不知道类型名）
- 不能在函数签名中写 lambda 类型
- 不同 lambda 即使签名相同也不能相互赋值

**A 正确：** 捕获列表确实变成 closure 类的成员变量。
```cpp
[x, &y] → struct { int x; int& y; };
```

**B 正确：** 默认 `operator()` 是 const，所以不能修改按值捕获的成员。`mutable` 关键字去掉这个 const，允许修改。

**C 正确：** 无捕获 lambda 可以转换为函数指针，因为它没有 state：
```cpp
auto f = [](int x) { return x + 1; };
int (*pf)(int) = f;   // OK
```
带捕获的不能（函数指针没空间放 state）。

**D 错误：** lambda 类型是**翻译单元内唯一**的。两个翻译单元里的同源码 lambda 是**不同类型**。这就是为什么 `std::function<R(Args...)>` 这样的类型擦除被广泛使用——它能存放任何匹配签名的可调用对象。

**来源：** 字节 C++ 面试（参考：cppreference、Scott Meyers EMC++ Item 31-34）

## Explanation

正确答案是 D。
选 D（说法错误）。
*lambda 本质：编译器生成的匿名 closure 类型。
每个 lambda 表达式生成一个唯一的匿名类（class），同源代码、同捕获列表、同函数体也是不同类型。这就是为什么： auto 是写 lambda 的唯一方式（你不知道类型名） 不能在函数签名中写 lambda 类型 不同 lambda 即使签名相同也不能相互赋值 *A 正确： 捕获列表确实变成 closure 类的成员变量。
