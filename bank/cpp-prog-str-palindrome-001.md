---
qid: cpp-prog-str-palindrome-001
type: prog
kp: [cpp-stl-basics]
primary_kp: cpp-stl-basics
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-str-palindrome-001/
---
判断字符串是否为回文：忽略大小写，只考虑字母与数字。

```cpp
#include <string>
bool isPalindrome(const std::string& s);
```