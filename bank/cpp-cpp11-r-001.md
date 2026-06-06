---
qid: cpp-cpp11-r-001
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: "B"
---

### 题目

阅读以下代码，`a` 和 `b` 的类型分别是什么？

```cpp
#include <iostream>

int main() {
    int x = 10;
    int& ref = x;
    auto a = ref;   // a 的类型？
    auto& b = ref;  // b 的类型？
    a = 99;
    b = 42;
    std::cout << x; // 输出什么？
}
```

A. `a` 是 `int&`，`b` 是 `int&`；输出 `99`
B. `a` 是 `int`，`b` 是 `int&`；输出 `42`
C. `a` 是 `int`，`b` 是 `int`；输出 `10`
D. `a` 是 `int&`，`b` 是 `int&`；输出 `42`

## Explanation

正确答案是 B。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 B 的表述“｀a｀ 是 ｀int｀，｀b｀ 是 ｀int&｀；输出 ｀42｀”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
