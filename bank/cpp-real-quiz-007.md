---
qid: cpp-real-quiz-007
type: single
kp: [cpp-types, cpp-arrays-pointers]
primary_kp: cpp-types
difficulty: hard
answer_key: B
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的输出是？

```cpp
#include <iostream>
int main() {
    std::cout << sizeof("") << ' ' << sizeof("a") << ' ' << sizeof("ab");
}
```

A. `0 1 2`
B. `1 2 3`
C. `1 1 2`
D. 实现定义

---

**解析：**

字符串字面值的类型是 `const char[N+1]`，其中 N 是字面值中的字符个数，**+1 是结尾的 `'\0'`**（[lex.string]）。

- `""` 类型是 `const char[1]`，只含 `'\0'`，`sizeof = 1`
- `"a"` 类型是 `const char[2]`（`'a'`,`'\0'`），`sizeof = 2`
- `"ab"` 类型是 `const char[3]`，`sizeof = 3`

易混淆答案 A：以为空字符串就是 0 字节，忘了 NUL 终结符；C 风格字符串 `'\0'` 永远占一个字节。

**来源：** C++ Brain Teasers；C++17 [lex.string]
