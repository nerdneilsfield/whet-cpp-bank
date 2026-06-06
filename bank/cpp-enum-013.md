---
qid: cpp-enum-013
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: A
---
以下代码能否通过编译？

```cpp
enum class Color : uint8_t;   // 前向声明

void process(Color c);        // 使用前向声明的枚举

enum class Color : uint8_t { Red, Green, Blue };  // 完整定义
```

A. 能编译，`enum class` 支持前向声明（需指定底层类型）
B. 编译错误：枚举不允许前向声明
C. 编译错误：`uint8_t` 不能作为底层类型
D. 编译错误：函数声明必须在枚举完整定义之后
