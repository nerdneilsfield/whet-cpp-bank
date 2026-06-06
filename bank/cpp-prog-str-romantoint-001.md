---
qid: cpp-prog-str-romantoint-001
type: prog
kp: [cpp-stl-basics]
primary_kp: cpp-stl-basics
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-str-romantoint-001/
---
罗马数字（合法、1..3999）转整数。处理减法形式 `IV/IX/XL/XC/CD/CM`。

```cpp
#include <string>
int romanToInt(const std::string& s);
```