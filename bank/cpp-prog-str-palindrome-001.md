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

## Explanation

使用左右双指针，跳过非字母数字字符，再把两侧字符转成小写后比较。只要出现不等就返回 false，指针交错则说明是回文。注意 `std::isalnum` 和 `std::tolower` 应传入 `unsigned char` 转换后的值，避免负 char 导致未定义行为。
