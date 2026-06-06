---
qid: cpp-real-bytedance-005
type: single
kp: [cpp-cpp14-17]
primary_kp: cpp-cpp14-17
difficulty: medium
answer_key: A
tags: [interview-real, bytedance]
---
```cpp
#include <tuple>
#include <array>

struct Point { int x; int y; };

std::tuple<int, double, std::string> tup{1, 3.14, "hello"};
std::array<int, 3> arr{1, 2, 3};
Point p{10, 20};

auto& [a, b, c] = tup;        // 1
auto [x, y, z] = arr;         // 2
auto& [px, py] = p;            // 3
```
关于 C++17 structured binding（结构化绑定）的三种数据源，以下说法**正确**的是：

A. structured binding 可作用于三类对象：**tuple-like 类型（如 std::tuple, std::pair, std::array）、原生数组、聚合类型（aggregate，所有成员都 public，无用户构造函数）**
B. structured binding 只能用于 std::tuple
C. structured binding 自动支持自定义类，无需任何条件
D. structured binding 在多线程下绑定是原子的，因此线程安全

---

**解析：**

选 A。C++17 引入的结构化绑定有**三种合法来源**：

**1. tuple-like 类型：**
要求满足三个条件：
- 特化了 `std::tuple_size<T>::value`（成员数量）
- 特化了 `std::tuple_element<I, T>::type`（每个成员的类型）
- 有 `get<I>(t)` 函数（成员函数或自由函数）

`std::tuple`、`std::pair`、`std::array` 都满足。**自定义类**也可以通过特化这些 trait 支持。

**2. 原生数组：**
```cpp
int arr[3] = {1, 2, 3};
auto [a, b, c] = arr;  // 元素个数必须与数组长度一致
```

**3. 聚合类型（aggregate）：**
所有非静态数据成员都 public、无用户提供的构造函数、无虚函数、无私有/受保护非静态成员等。
```cpp
struct Point { int x, y; };   // 聚合
Point p{1, 2};
auto [x, y] = p;
```

**注意点：**
- `auto [a, b] = expr;` 拷贝；`auto& [a, b] = expr;` 引用；`const auto& [a, b] = expr;` 只读引用
- 名字不是"引用"——它们是匿名 unnamed object 的成员的别名（对于 tuple-like 是 reference，对 aggregate 实质相同）
- C++20 可在 lambda 捕获列表里用 `[a, b, c]`

**D 错：** structured binding 是编译期语法糖，与线程安全无关。

**来源：** 字节 C++17 面试（参考：cppreference structured bindings、Bjarne Stroustrup《The C++ Programming Language》）