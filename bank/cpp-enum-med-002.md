---
qid: cpp-enum-med-002
type: single
kp: [cpp-enum]
difficulty: medium
answer_key: D
---

C++ 枚举的底层类型（underlying type）及其取值范围存在陷阱。以下代码输出是？

```cpp
#include <iostream>
int main() {
    enum class E : unsigned char { A = 200, B = 300 };
    std::cout << static_cast<int>(E::B) << '\n';
}
```

A. 300
B. 44（`200 + 100 = 300` 溢出只保留 8 位）
C. 编译失败，因为 300 超出 `unsigned char` 范围
D. 实现定义行为，或编译失败（取决于编译器）

---

**解析：**

C++ 标准规定：枚举值不一定在底层类型的范围内，前提是指定值超出范围时，行为是实现定义的（[dcl.enum]/5）。底层类型 `unsigned char` 的范围是 `[0, 255]`，300 超出该范围。

实际实现：Clang 编译失败（error: enumerator value is not representable in the underlying type），GCC 发出警告但只取低 8 位（44）。标准不要求编译器做默认截断，因此跨平台不可移植。

这和"枚举整型溢出"实际上是一类问题——不同编译器处理不同。

## 解析

正确答案是 D。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。选项 D 的表述“实现定义行为，或编译失败（取决于编译器）”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
