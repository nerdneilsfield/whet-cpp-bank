---
qid: cpp-operators-007
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: C
---

以下代码的输出结果是什么？

```cpp
#include <iostream>
int main() {
    int a = 3, b = 5;
    std::cout << (a > b) << std::endl;
    return 0;
}
```

A. 3
B. 5
C. 0
D. 1

## Explanation

正确答案是 C，因为该选项对应 `0`，符合题中代码或概念的 C++ 语义。运算符题的关键是先按 C++ 的优先级、结合性和求值规则拆表达式，再判断每一步的值。常见误区是把按位运算和逻辑运算混淆，或误以为所有二元运算都会短路求值。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
