---
qid: cpp-operators-r-002
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: A
---

# 代码阅读：位运算优先级陷阱

```cpp
#include <iostream>
int main() {
    int a = 2, b = 3, c = 1;
    if (a & b == c)
        std::cout << "true\n";
    else
        std::cout << "false\n";
}
```

输出是什么？（注意：`==` 的优先级高于 `&`）

A. `false`（等价于 `a & (b == c)`，即 `2 & 0 == 0`，结果为 `false`）  
B. `true`（等价于 `(a & b) == c`，即 `2 == 1`，结果为 `false`——也不对）  
C. 编译错误  
D. `true`（因为 `2 & 3 == 1` 为真）

> 陷阱提示：`==` 优先级高于 `&`，实际求值顺序为 `a & (b == c)`。

## 解析

正确答案是 A，因为该选项对应 ``false`（等价于 `a & (b == c)`，即 `2 & 0 == 0`，结果为 `false`）`，符合题中代码或概念的 C++ 语义。运算符题的关键是先按 C++ 的优先级、结合性和求值规则拆表达式，再判断每一步的值。常见误区是把按位运算和逻辑运算混淆，或误以为所有二元运算都会短路求值。 B 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
