---
qid: cpp-enum-008
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---
以下代码输出什么？

```cpp
#include <iostream>
enum Status { Ok = 0, Warn = 10, Error = 20 };
int main() {
    std::cout << Warn;
}
```

A. 0
B. 10
C. 1
D. 编译错误

## 解析

正确答案是 B。枚举题的核心是区分传统 `enum` 与 `enum class` 的作用域、隐式转换和底层类型规则。选项 B 的表述“10”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
