---
qid: cpp-types-med-003
type: single
kp: [cpp-types]
difficulty: medium
answer_key: B
---
下列代码中 `x` 和 `y` 的类型分别是？

```cpp
#include <iostream>
int main() {
    int v = 42;
    const int& r = v;
    auto x = r;
    auto& y = r;
    std::cout << std::is_same_v<decltype(x), int>;
    std::cout << std::is_same_v<decltype(y), const int&>;
    return 0;
}
```

A. `x` 是 `const int&`，`y` 是 `const int&`
B. `x` 是 `int`，`y` 是 `const int&`
C. `x` 是 `const int`，`y` 是 `const int&`
D. `x` 是 `int`，`y` 是 `int&`

---

**解析：**

`auto` 推导时总会剥去引用和顶层 cv 限定符，因此 `auto x = r;` 中 `r` 是 `const int&`，推导后 `x` 为 `int`（复制一份）。而 `auto& y = r;` 显式声明为引用，推导结果为 `const int&`，`const` 得以保留因为底层 const 不被剥去。这是 C++ auto 推导的一大常考点：有没有 `&` 天差地别。

## 解析

正确答案是 B，即 `x` 是 `int`，`y` 是 `const int&`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
