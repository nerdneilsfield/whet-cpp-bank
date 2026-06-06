---
qid: cpp-real-quiz-008
type: single
kp: [cpp-classes, cpp-scope-linkage]
primary_kp: cpp-scope-linkage
difficulty: hard
answer_key: C
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++14 标准，以下程序的行为是？

```cpp
#include <iostream>
struct S { static const int n = 42; };
int main() {
    const int& r = S::n;     // ODR-use
    std::cout << r;
}
```

（假设没有在任何 .cpp 中写 `const int S::n;` 这样的命名空间作用域定义）

A. 输出 `42`
B. 输出 `0`
C. 链接错误（undefined reference to `S::n`）
D. 编译错误

---

**解析：**

[basic.def.odr]：取 `static const int n = 42` 的地址或绑定到引用属于 **ODR-use**。仅有类内 in-class initializer 算 declaration，**还需要类外定义** `const int S::n;` 才能 ODR-use，否则链接器找不到符号。

`const int& r = S::n` 将引用绑定到 `S::n`，因此 ODR-use 触发，但没有定义，**链接失败**（"undefined reference"）。

如果改成 `std::cout << S::n;`，C++17 之前也会 ODR-use（流插入按值取参但还是要走引用解析路径，实践上多数编译器允许并优化掉）。C++17 起 inline static member 解决了这个痛点：写 `inline static const int n = 42;` 就不再需要 OOL 定义。

**来源：** cppquiz.org Question #4；C++14 [basic.def.odr]
