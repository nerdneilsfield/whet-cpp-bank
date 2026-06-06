---
qid: cpp-cpp11-r-001
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: "B"
---

## 题目

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

## 解析

`auto` 推导时**去掉顶层引用**：`auto a = ref` 中 `a` 的类型是 `int`（值拷贝），修改 `a` 不影响 `x`。`auto& b = ref` 显式声明引用，`b` 绑定到 `x`，`b = 42` 修改 `x`。最终 `x` 输出 `42`。
