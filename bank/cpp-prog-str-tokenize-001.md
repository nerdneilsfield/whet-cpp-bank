---
qid: cpp-prog-str-tokenize-001
type: prog
kp: [cpp-stl-basics]
primary_kp: cpp-stl-basics
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-str-tokenize-001/
---
按单字符分隔符 `delim` 切分字符串为 `vector<string>`。连续分隔符产生空 token，开头/结尾的分隔符也产生空 token。空串返回 `{""}`。

```cpp
#include <string>
#include <vector>
std::vector<std::string> split(const std::string& s, char delim);
```