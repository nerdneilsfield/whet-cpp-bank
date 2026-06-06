---
qid: cpp-enum-012
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: C
---
以下 switch 代码的输出是什么？

```cpp
#include <iostream>
enum class Season { Spring, Summer, Autumn, Winter };
int main() {
    Season s = Season::Autumn;
    switch (s) {
        case Season::Spring:  std::cout << "S"; break;
        case Season::Summer:  std::cout << "U"; break;
        case Season::Autumn:  std::cout << "A"; break;
        case Season::Winter:  std::cout << "W"; break;
    }
}
```

A. S
B. U
C. A
D. W

## Explanation

正确答案是 C。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。选项 C 的表述“A”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
