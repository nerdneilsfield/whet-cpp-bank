---
qid: cpp-prog-ds-hashmap-firstunique-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-ds-hashmap-firstunique-001/
---
返回字符串中第一个只出现一次的字符的下标；不存在则返回 -1。两遍扫描+计数。

```cpp
#include <string>
int firstUniqChar(const std::string& s);
```