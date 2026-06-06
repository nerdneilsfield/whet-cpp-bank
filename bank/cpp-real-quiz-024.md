---
qid: cpp-real-quiz-024
type: single
kp: [cpp-arrays-pointers]
primary_kp: cpp-arrays-pointers
difficulty: hard
answer_key: A
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的输出是？

```cpp
#include <iostream>
int main() {
    const char* s = "abcdef";
    std::cout << s + 2;
}
```

A. `cdef`
B. `abcdef2`
C. 编译错误（const char* 不能加 int）
D. 行为未定义

---

**解析：**

`"abcdef"` 的类型是 `const char[7]`，赋值给 `s` 时退化为指向首元素的指针 `const char*`。

`s + 2` 是**指针算术运算**（[expr.add]/4）：`s` 指向第一个字符 `'a'`，`s + 2` 指向 `'a' + 2 = 'c'` 之后 0 偏移 —— 等效于 `&s[2]`。

`std::cout << s + 2` 将 `const char*` 解释为 C 风格字符串，从 `'c'` 开始输出直到 `'\0'` → `"cdef"`。

这就是为什么 C++ 中 `"abc" + 1` 不是字符串拼接而是指针算术的经典坑。如果你想要拼接，用 `std::string`：`std::string("ab") + std::string("cd")`。

**来源：** cppquiz.org（多题考点）；C++17 [expr.add]/4