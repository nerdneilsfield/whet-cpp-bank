---
qid: cpp-enum-014
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---
以下代码输出什么？

```cpp
#include <iostream>
enum Color { Red = 1, Green = 1, Blue = 2 };
int main() {
    std::cout << (Red == Green);
}
```

A. 0
B. 1
C. 编译错误：不允许两个枚举器值相同
D. 未定义行为

## 解析

正确答案是 B。枚举题的核心是区分传统 `enum` 与 `enum class` 的作用域、隐式转换和底层类型规则。选项 B 的表述“1”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
