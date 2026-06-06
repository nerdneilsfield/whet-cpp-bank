---
qid: cpp-mod-multi-med-004
type: multi
kp: [cpp-cpp11]
difficulty: medium
answer_key: [B, C]
---
关于 `constexpr` 函数的约束，**哪些说法是正确的**？（多选）

```cpp
constexpr int f(int n) {
    int s = 0;
    for (int i = 0; i < n; ++i) s += i;
    return s;
}
```

A. 在 C++11 中，`constexpr` 函数体允许包含 `for` 循环和局部变量声明
B. C++14 起，`constexpr` 函数体可以包含循环、多条语句、可变的局部变量
C. C++20 起，`constexpr` 函数中允许使用 `try`/`catch`（但常量求值时不能抛异常），也允许 `virtual`
D. 一个 `constexpr` 函数被调用时**必定**在编译期求值

---

**解析：**

A 错误：C++11 的 `constexpr` 函数体被严格限制为单条 `return` 语句（加上 typedef、using、static_assert 等），不允许循环或可变局部变量。
B 正确：C++14 大幅放宽限制，允许多条语句、循环、可变局部变量、条件分支等。
C 正确：C++20 允许 `constexpr` 函数包含 `try-catch`（但常量求值上下文中不能真的抛出）、允许 `virtual` 函数为 `constexpr`、允许 `dynamic_cast` 等。
D 错误：`constexpr` 函数**仅**在所有实参为常量表达式且需要常量求值上下文（如数组维度、模板实参）时才在编译期求值；否则按普通函数运行期调用。若必须在编译期求值，应使用 `consteval`（C++20）。

## Explanation

正确答案是 [B, C]。B 正确：C++14 大幅放宽限制，允许多条语句、循环、可变局部变量、条件分支等。
工程上要理解现代 C++ 语法背后的推导、重载和生命周期规则，而不是只按表面写法判断。
A 错误：C++11 的 `constexpr` 函数体被严格限制为单条 `return` 语句（加上 typedef、using、static_assert 等），不允许循环或可变局部变量。
