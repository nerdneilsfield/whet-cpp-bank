---
qid: cpp-prog-ds-stack-paren-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-ds-stack-paren-001/
---
用 `std::stack` 判断括号串是否合法（支持 `()[]{}`）。

```cpp
#include <string>
bool isBalanced(const std::string& s);
```