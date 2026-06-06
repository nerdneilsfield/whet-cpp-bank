---
qid: cpp-real-quiz-005
type: single
kp: [cpp-types]
primary_kp: cpp-types
difficulty: hard
answer_key: D
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <iostream>
int main() {
    char c = -1;
    if (c < 0) std::cout << "signed";
    else       std::cout << "unsigned";
}
```

A. 保证输出 `signed`
B. 保证输出 `unsigned`
C. 编译错误
D. 实现定义（视编译器/平台而定）

---

**解析：**

C++ 标准把 `char`、`signed char`、`unsigned char` 视为**三种不同类型**。`char` 的有无符号性是**实现定义**（[basic.fundamental]/1）：x86 上 GCC/Clang 默认 `char` 是 signed，输出 `signed`；ARM 上很多编译器 `char` 默认 unsigned，`-1` 隐式转换为 `255`，输出 `unsigned`。

如果你想要保证有符号性，应该显式写 `signed char` 或 `unsigned char`，不要用裸 `char` 做算术。

易混淆答案 A：很多桌面平台确实输出 `signed`，但这是平台默认，而非标准保证。

**来源：** cppquiz.org Question #41；C++17 [basic.fundamental]/1

## Explanation

正确答案是 D。
C++ 标准把 char、signed char、unsigned char 视为三种不同类型。char 的有无符号性是实现定义（[basic.fundamental]/1）：x86 上 GCC/Clang 默认 char 是 signed，输出 signed；ARM 上很多编译器 char 默认 unsigned，-1 隐式转换为 255，输出 unsigned。
如果你想要保证有符号性，应该显式写 signed char 或 unsigned char，不要用裸 char 做算术。
易混淆答案 A：很多桌面平台确实输出 signed，但这是平台默认，而非标准保证。
