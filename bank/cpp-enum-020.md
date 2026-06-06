---
qid: cpp-enum-020
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---
以下代码输出什么？

```cpp
#include <iostream>
enum class State { Idle = 0, Running, Paused, Stopped };
int main() {
    State s1 = State::Running;
    State s2 = State::Running;
    State s3 = State::Paused;
    std::cout << (s1 == s2) << (s1 == s3);
}
```

A. 00
B. 10
C. 01
D. 编译错误

## 解析

正确答案是 B。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。选项 B 的表述“10”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
