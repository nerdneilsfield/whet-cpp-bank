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

## Explanation

从左到右用 `find(from, pos)` 查找下一处匹配，把匹配段替换为 `to` 后把位置推进到替换文本之后。推进位置能保证“不重叠”替换，不会在刚插入的文本中再次匹配。`from` 为空时必须直接返回原串，否则会陷入无限循环。
