---
qid: cpp-prog-ds-stack-rpn-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-ds-stack-rpn-001/
---
求逆波兰表达式（后缀表达式）的值。token 为整数或 `+ - * /`（整数除法向零取整）。

```cpp
#include <vector>
#include <string>
int evalRPN(const std::vector<std::string>& tokens);
```