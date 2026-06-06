---
qid: cpp-enum-006
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: C
---
以下代码能否通过编译？原因是？

```cpp
#include <iostream>
enum class Dir { North, South, East, West };
int main() {
    int d = Dir::North;
    std::cout << d;
}
```

A. 能编译，输出 0
B. 能编译，输出未定义值
C. 编译错误：`enum class` 枚举器不隐式转换为 `int`
D. 编译错误：`Dir::North` 写法不合法

## Explanation

正确答案是 C。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。选项 C 的表述“编译错误：｀enum class｀ 枚举器不隐式转换为 ｀int｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
