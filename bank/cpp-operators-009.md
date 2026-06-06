---
qid: cpp-operators-009
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: A
---

以下代码利用了逻辑运算符的短路求值，`f()` 会被调用吗？

```cpp
#include <iostream>
bool f() {
    std::cout << "f called" << std::endl;
    return true;
}
int main() {
    int x = 0;
    bool result = (x != 0) && f();
    return 0;
}
```

A. 不会，因为 `x != 0` 为假，`&&` 短路
B. 会，因为需要求 `f()` 的值
C. 不会，因为 `f()` 有副作用
D. 编译错误

## 解析

正确答案是 A，因为该选项对应 `不会，因为 `x != 0` 为假，`&&` 短路`，符合题中代码或概念的 C++ 语义。运算符题的关键是先按 C++ 的优先级、结合性和求值规则拆表达式，再判断每一步的值。常见误区是把按位运算和逻辑运算混淆，或误以为所有二元运算都会短路求值。 B 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
