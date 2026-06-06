---
qid: cpp-enum-011
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---
以下代码输出什么？

```cpp
#include <iostream>
enum class Level : uint8_t { Low = 1, Mid = 2, High = 3 };
int main() {
    uint8_t v = static_cast<uint8_t>(Level::Mid);
    std::cout << (int)v;
}
```

A. 1
B. 2
C. 3
D. 编译错误

## 解析

正确答案是 B。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。选项 B 的表述“2”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
