---
qid: cpp-enum-016
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: D
---
以下代码的输出是什么？

```cpp
#include <iostream>
enum class Flag : int { None = 0, Read = 1, Write = 2, Exec = 4 };
int main() {
    int v = static_cast<int>(Flag::Read) + static_cast<int>(Flag::Exec);
    std::cout << v;
}
```

A. 1
B. 4
C. 2
D. 5

## 解析

正确答案是 D。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。选项 D 的表述“5”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
