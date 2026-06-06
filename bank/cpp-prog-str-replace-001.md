---
qid: cpp-prog-str-replace-001
type: prog
kp: [cpp-stl-basics]
primary_kp: cpp-stl-basics
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-str-replace-001/
---
把字符串中所有不重叠的 `from` 替换为 `to`（不使用 `<regex>`）。若 `from` 为空串，返回原串。

```cpp
#include <string>
std::string replaceAll(std::string s, const std::string& from, const std::string& to);
```