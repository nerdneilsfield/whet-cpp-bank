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

## Explanation

遇到左括号入栈，遇到右括号时检查栈顶是否为匹配的左括号并弹出。遍历结束后栈为空才合法。注意空串应为合法，且遇到不匹配或栈空的右括号要立即返回 false。
