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

## Explanation

遍历 token，数字入栈，遇到运算符就弹出右操作数和左操作数，按顺序计算后压回。`-` 和 `/` 对操作数顺序敏感，不能写反；C++ 整数除法本身就是向零截断。最终栈顶即表达式值，测试通常保证表达式合法。
