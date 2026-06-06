---
qid: cpp-real-quiz-014
type: single
kp: [cpp-scope-linkage, cpp-classes]
primary_kp: cpp-scope-linkage
difficulty: medium
answer_key: C
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <iostream>
int foo() { return 42; }
int main() {
    const int& r = foo();   // (1)
    int&       s = foo();   // (2)
    std::cout << r << ' ' << s;
}
```

A. 输出 `42 42`
B. 输出 `42`，然后（2）处 UB
C. （2）编译错误
D. 两行都编译错误

---

**解析：**

(1) `const int& r = foo();` **合法**：const 引用可以绑定到临时对象（[dcl.init.ref]/5.4.1），临时 `int(42)` 的生命周期**延长**到引用的作用域结束（`main()` 结束时）。

(2) `int& s = foo();` **编译错误**：普通（非 const）左值引用不能绑定到右值/临时对象。不能 `int&` 绑一个 prvalue `int`。

易混淆项 B：以为 `s` 会绑定到临时然后临时析构为悬空引用（UB）——但这里不是 UB，而是一开始就**不能编译**。

**来源：** C++ Brain Teasers；C++17 [dcl.init.ref]/5