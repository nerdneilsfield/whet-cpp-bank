---
qid: cpp-enum-r-003
type: fill
kp: [cpp-enum]
difficulty: easy
answer_key: "`static_cast<int>(lv)`"
---

## 题目

下面代码有一处错误，填写正确的替换方式使代码能输出 `1`。

```cpp
#include <iostream>

enum class Level { Low, Medium, High };

int main() {
    Level lv = Level::Medium;
    int n = lv;  // 错误在此行
    std::cout << n << std::endl;
    return 0;
}
```

将 `int n = lv;` 改为：`int n = _________;`

## 答案

`static_cast<int>(lv)`

## 解析

`enum class` 不允许隐式转换为整数类型，必须使用 `static_cast<int>()` 显式转换。`Level::Medium` 的枚举值为 `1`（从 0 开始，Low=0，Medium=1），所以转换后 `n` 的值为 `1`。
