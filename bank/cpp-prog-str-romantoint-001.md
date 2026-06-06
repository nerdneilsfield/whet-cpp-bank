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

## Explanation

把每个罗马字符映射为数值，从左到右扫描；若当前值小于右侧下一值，则减去当前值，否则加上当前值。这样可统一处理 IV、IX、XL、XC、CD、CM 等减法形式。题目保证输入合法，因此不必实现完整合法性校验。
