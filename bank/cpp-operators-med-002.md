---
qid: cpp-operators-med-002
type: single
kp: [cpp-operators]
difficulty: medium
answer_key: B
---
下列代码输出是？

```cpp
#include <iostream>
int f() { std::cout << "f"; return 0; }
int g() { std::cout << "g"; return 1; }
int main() {
    if (g() || f()) {}
    if (f() && g()) {}
    return 0;
}
```

A. fgfg
B. gf
C. gfg
D. fg

---

**解析：**

`||` 与 `&&` 具有短路求值语义，且严格从左到右求值（这是 C++ 标准对这两个运算符的特殊保证）。第一句 `g() || f()`：`g()` 输出 `g` 并返回 `1`（真），因短路 `f()` 不再求值；第二句 `f() && g()`：`f()` 输出 `f` 并返回 `0`（假），因短路 `g()` 不再求值。故总输出为 `gf`。注意短路只适用于内建 `||`/`&&`，重载后的版本没有短路语义。
