---
qid: cpp-enum-r-002
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: C
---

## 题目

下面代码的输出是什么？

```cpp
#include <iostream>

enum Direction { North, East, South, West };

int main() {
    Direction d = South;
    int val = d;
    std::cout << val << std::endl;
    return 0;
}
```

A. 编译错误
B. `0`
C. `2`
D. `South`

## 答案

C

## 解析

正确答案是 C。传统 `enum` 的枚举器会进入外层作用域，并且通常可隐式转换为整数。选项 C 的表述“｀2｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
