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

## Explanation

从起始位置开始反复查找分隔符，把当前位置到分隔符前的子串加入结果，并把当前位置移到分隔符后一位。连续分隔符会产生长度为 0 的子串，开头和结尾的分隔符也会自然产生空 token。空字符串没有分隔符时应返回包含一个空串的 vector。
