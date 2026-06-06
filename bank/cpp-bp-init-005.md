---
qid: cpp-bp-init-005
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: D
---

下面的"static init fiasco"代码可能在运行时产生什么结果？

```cpp
// a.cpp
extern int x;
int y = x * 2;

// b.cpp
extern int y;
int x = 42;

// main.cpp
extern int x, y;
int main() {
    std::cout << x << " " << y;
}
```

A. 必然输出 "42 84"
B. 必然输出 "42 0"
C. 编译错误
D. 输出依赖编译器/链接器对 TU 的初始化顺序，可能是 "42 0" 或 "42 84"

---

## Explanation

**Static Initialization Order Fiasco（静态初始化顺序问题）**：

C++ 规定**同一 TU 内**的命名空间作用域非局部对象，按定义顺序初始化。但**跨 TU** 之间的初始化顺序**未指定**（unspecified）——链接器可以按任何顺序排列 TU 的全局构造调用。

本例：
- 如果 `a.cpp` 先于 `b.cpp` 初始化：`y = x * 2` 时 `x` 还是 0（zero-init 阶段），所以 `y = 0`
- 如果 `b.cpp` 先：`x = 42`，然后 `y = 42 * 2 = 84`

两种结果都是合法行为。**这种 bug 在测试机 OK 但生产机崩溃**，因不同链接器、不同 .o 顺序、不同链接选项都可能改变顺序。

工程解决方案：

1. **Construct-on-first-use idiom**：
```cpp
int& y() {
    static int instance = x() * 2;  // 首次调用时初始化，线程安全(C++11)
    return instance;
}
```

2. **constinit / constexpr**：编译期初始化彻底绕过顺序问题：
```cpp
constexpr int x = 42;
constexpr int y = x * 2;
```

3. **避免跨 TU 静态依赖**：把相关全局放同一个 TU；或者用 Meyer's singleton。

4. **C++20 `constinit`**：保证编译期初始化（如果可能），无运行时初始化顺序问题：
```cpp
constinit int x = 42;  // 编译期初始化
```
