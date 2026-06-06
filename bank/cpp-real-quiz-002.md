---
qid: cpp-real-quiz-002
type: single
kp: [cpp-cpp11, cpp-casting]
primary_kp: cpp-casting
difficulty: hard
answer_key: C
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <iostream>
int main() {
    int a = int(1.9);
    int b = int{1.9};
    std::cout << a << ' ' << b;
}
```

A. 输出 `1 1`
B. 输出 `1 2`
C. 编译错误
D. 行为未定义

---

**解析：**

`int(1.9)` 是**函数式（C 风格）转换**，等价于 `(int)1.9`，允许 narrowing，把 `1.9` 截断成 `1`，合法。

`int{1.9}` 是 **list-initialization**，按 [dcl.init.list]/7 禁止 narrowing conversion。`double → int` 永远是 narrowing（除非源是常量表达式且能精确表示，1.9 显然不能精确表示为 int），所以**编译错误**。

很多人以为 `int(x)` 和 `int{x}` 等价，这正是 C++11 想消灭的隐式截断陷阱：用 `{}` 初始化时编译器会拒绝有损转换。

**来源：** C++ Brain Teasers Teaser #2；C++17 [dcl.init.list]/7
