---
qid: cpp-real-quiz-028
type: single
kp: [cpp-cpp11, cpp-functions]
primary_kp: cpp-cpp11
difficulty: medium
answer_key: A
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <iostream>
constexpr int square(int x) { return x * x; }

int main() {
    int n;
    std::cin >> n;             // 运行期才能拿到 n
    std::cout << square(n);    // (1)
}
```

A. 合法，`square(n)` 在运行期被调用并返回 `n * n`
B. 编译错误：constexpr 函数只能在编译期调用
C. 行为未定义
D. 链接错误

---

**解析：**

[dcl.constexpr]/7：`constexpr` 函数**既可在编译期调用也可在运行期调用**。`constexpr` 是"能在编译期被调用"，**不是**"只能在编译期被调用"。

实参为常量表达式（如 `square(5)`）时，**可以**作为常量表达式参与编译期求值；实参为运行期值（如 `square(n)`）时，**退化为普通函数调用**，无任何问题。

如果要强制必须编译期求值，C++20 引入了 **`consteval`** 关键字（"immediate function"）。`consteval int f(...)` 在运行期上下文调用就编译错误。

易混淆答案 B：很多人把 `constexpr` 误解成 `consteval`。两者关键差异：
- `constexpr`：能在编译期算 → 可以；不能也 OK
- `consteval`：必须在编译期算 → 不能就编译错误

**来源：** C++17 [dcl.constexpr]/7；C++20 P1073R3（consteval）

## Explanation

正确答案是 A。
[dcl.constexpr]/7：constexpr 函数既可在编译期调用也可在运行期调用；constexpr 是"能在编译期被调用"，不是"只能在编译期被调用"。
实参为常量表达式（如 square(5)）时，可以作为常量表达式参与编译期求值；实参为运行期值（如 square(n)）时，退化为普通函数调用，无任何问题；如果要强制必须编译期求值，C++20 引入了 consteval 关键字（"immediate function"）。
consteval int f(...) 在运行期上下文调用就编译错误。
