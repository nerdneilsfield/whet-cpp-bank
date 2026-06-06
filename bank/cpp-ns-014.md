---
qid: cpp-ns-014
type: fill
kp: [cpp-preprocessor]
difficulty: easy
answer_key: "namespace fs = std::filesystem"
---

为 `std::filesystem` 创建别名 `fs` 的写法是：

```cpp
______;
```

## 解析

填空应为 `namespace fs = std::filesystem`，因为这是题干所问概念或语法在 C++ 中的标准写法。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
