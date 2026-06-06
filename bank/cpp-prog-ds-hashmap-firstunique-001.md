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

## Explanation

先遍历字符串统计每个字符出现次数，再第二次从左到右查找计数为 1 的位置。两遍扫描能保证返回的是第一个唯一字符，而不是任意唯一字符。注意不存在时返回 -1，字符作为数组下标时应转换为 `unsigned char` 或使用 map 避免负值问题。
