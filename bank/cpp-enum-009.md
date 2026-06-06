---
qid: cpp-enum-009
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: A
---
以下代码中 `c` 和 `d` 的值分别是多少？

```cpp
enum Fruit { Apple, Banana = 5, Cherry, Durian };
// c = Cherry, d = Durian
```

A. c=6, d=7
B. c=5, d=6
C. c=2, d=3
D. 编译错误

## Explanation

正确答案是 A。枚举题的核心是区分传统 `enum` 与 `enum class` 的作用域、隐式转换和底层类型规则。选项 A 的表述“c=6, d=7”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
