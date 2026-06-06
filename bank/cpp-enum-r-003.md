---
qid: cpp-enum-r-003
type: fill
kp: [cpp-enum]
difficulty: easy
answer_key: "`static_cast<int>(lv)`"
---

### 题目

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

## Explanation

`static_cast<int>(lv)`


应填 ``static_cast<int>(lv)``。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
