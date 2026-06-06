---
qid: cpp-cpp11-012
type: fill
kp: [cpp-cpp11]
difficulty: easy
answer_key: "6"
---

# 代码阅读：constexpr 函数求值

阅读以下代码，`result` 的值是多少？

```cpp
constexpr int square(int n) { return n * n; }

int main() {
    constexpr int result = square(2) + square(1) + square(1);
    // result = ?
}
```

`result` 的值为：___

## 解析

应填 `6`。`constexpr` 表示可在编译期求值，适用于需要常量表达式的场合。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
