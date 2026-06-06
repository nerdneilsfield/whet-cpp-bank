---
qid: cpp-real-quiz-003
type: single
kp: [cpp-undefined-behavior, cpp-operators]
primary_kp: cpp-undefined-behavior
difficulty: hard
answer_key: A
tags: [interview-real, cppquiz, language-lawyer]
---
根据 **C++14** 标准，以下程序的行为是？

```cpp
#include <iostream>
int main() {
    int i = 7;
    i = i++;
    std::cout << i;
}
```

A. 行为未定义
B. 输出 `7`
C. 输出 `8`
D. 编译错误

---

**解析：**

在 C++14 及以前，`i = i++` 中赋值左侧 `i` 的取值和 `i++` 对 `i` 的修改之间**没有 sequenced-before 关系**（[basic.exec]/15 旧版），对同一标量两个未排序的副作用 → **未定义行为**。

C++17 修复了赋值表达式的求值顺序（[expr.ass]/1：右操作数在左操作数之前求值，但 `i++` 的 side-effect 仍可能与左侧 `i` 的左值计算未排序），实际上 `i = i++` 在 C++17 才变得 well-defined 并保留旧值。

题目锁定 C++14，所以是 UB。这是 cppquiz 的经典老题，新人常以为"反正赋值就行了"。

**来源：** cppquiz.org Question #2（C++14 [basic.exec]/15）

## Explanation

正确答案是 A。
在 C++14 及以前，i = i++ 中赋值左侧 i 的取值和 i++ 对 i 的修改之间没有 sequenced-before 关系（[basic.exec]/15 旧版），对同一标量两个未排序的副作用 → 未定义行为。
C++17 修复了赋值表达式的求值顺序（[expr.ass]/1：右操作数在左操作数之前求值，但 i++ 的 side-effect 仍可能与左侧 i 的左值计算未排序），实际上 i = i++ 在 C++17 才变得 well-defined 并保留旧值。
题目锁定 C++14，所以是 UB。这是 cppquiz 的经典老题，新人常以为"反正赋值就行了"。
