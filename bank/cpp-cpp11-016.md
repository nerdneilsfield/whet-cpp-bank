---
qid: cpp-cpp11-016
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: D
---

# 代码阅读：decltype 推导类型

阅读以下代码，`y` 的类型是什么？

```cpp
int x = 10;
int& ref = x;
decltype(ref) y = x;
```

A. `int`
B. `int*`
C. `const int&`
D. `int&`

## Explanation

正确答案是 D。`decltype(expr)` 关注表达式的精确类型和值类别，因此会保留引用等信息。选项 D 的表述“｀int&｀”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
